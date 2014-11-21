#include <Buffer.h>
#include <FastMath.h>


void Buffer::DrawLine(const Coord2D p1, const Coord2D p2, const Color c1,
		const Color c2)
{
	// compléter ici
	int y = p1.y, x = p1.x;
	int longX = p2.x - p1.x, longY = p2.y - p1.y;
    int const2 = 0, const1 = 0, critere = 0;
    Color c = c1;
    double wa = 0.0, wb = 0.0;
    int incX = 0, incY = 0;
    int compteur = 0;

    if(longX >= 0){
        incX++;
    }
    else{
        incX--;
        longX *= (-1);
    }

    if(longY >= 0){
        incY++;
    }
    else{
        incY--;
        longY *= (-1);
    }

    if(longY < longX){
        const1 = 2 * (longY - longX);
        const2 = 2*longY;
        critere =  const2 - longX;
        for(compteur=1; compteur <= longX; compteur++){
            wa = 1 - (sqrt((p1.x - x)*(p1.x - x)+(p1.y - y)*(p1.y - y)))/(sqrt((p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y)));
            wb = 1- wa;

            c.red =  (1/(wa+ wb)) * (wa*c1.red + wb*c2.red);
            c.blue =  (1/(wa+ wb)) * (wa*c1.blue + wb*c2.blue);
            c.green =  (1/(wa+ wb)) * (wa*c1.green + wb*c2.green);

            SetPoint(Coord2D(x, y), c);
            if(critere > 0){
                y = y + incY;
                critere = critere + const1;
            }
            else{
                critere = critere + const2;
            }
            x = x +incX;
        }
    }
    else{
        const1 = 2 * (longX - longY);
        const2 = 2*longX;
        critere =  const2 - longY;
        for(compteur=1; compteur <= longY; compteur++){
            wa = 1 - (sqrt((p1.x - x)*(p1.x - x)+(p1.y - y)*(p1.y - y)))/(sqrt((p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y)));
            wb = 1- wa;

            c.red =  (1/(wa+ wb)) * (wa*c1.red + wb*c2.red);
            c.blue =  (1/(wa+ wb)) * (wa*c1.blue + wb*c2.blue);
            c.green =  (1/(wa+ wb)) * (wa*c1.green + wb*c2.green);

            SetPoint(Coord2D(x, y), c);
            if(critere > 0){
                x = x + incX;
                critere = critere + const1;
            }
            else{
                critere = critere + const2;
            }
            y = y +incY;
        }
    }

}

void Buffer::DrawFilledTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3)
{
	// completer ici
	Coord2D m1, m2;
	Color color1, color2;
	double wa, wb, wc;

    scanLineComputer.Init();
    scanLineComputer.Compute(p1, p2, p3);
    for(int i=scanLineComputer.ymin; i<=scanLineComputer.ymax; i++){
        // point à gauche
        m1 = Coord2D(scanLineComputer.left.data[i],i);

        wa = scanLineComputer.leftweight.data[i].data[0];
        wb = scanLineComputer.leftweight.data[i].data[1];
        wc = scanLineComputer.leftweight.data[i].data[2];

        color1.red =  (1/(wa+ wb + wc)) * (wa*c1.red + wb*c2.red + wc*c3.red);
        color1.blue =  (1/(wa+ wb + wc)) * (wa*c1.blue + wb*c2.blue + wc*c3.blue);
        color1.green =  (1/(wa+ wb + wc)) * (wa*c1.green + wb*c2.green + wc*c3.green);

        // point à droite
        m2 = Coord2D(scanLineComputer.right.data[i], i);
        wa = scanLineComputer.rightweight.data[i].data[0];
        wb = scanLineComputer.rightweight.data[i].data[1];
        wc = scanLineComputer.rightweight.data[i].data[2];

        color2.red =  (1/(wa+ wb + wc)) * (wa*c1.red + wb*c2.red + wc*c3.red);
        color2.blue =  (1/(wa+ wb + wc)) * (wa*c1.blue + wb*c2.blue + wc*c3.blue);
        color2.green =  (1/(wa+ wb + wc)) * (wa*c1.green + wb*c2.green + wc*c3.green);
        DrawLine(m1, m2, color1, color2);
    }




}

void Buffer::DrawPhongTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3,
		const Coord3D posi1, const Coord3D posi2, const Coord3D posi3,
		const Coord3D normal1, const Coord3D normal2, const Coord3D normal3,
		const AmbientLight & ambientLight, const PointLight & pointLight)
{
	// compléter ici
    Coord2D rightPt, leftPt, currentPt;
    Coord3D interpolateNormal, currentNormal, currentPos, interpolatePt;
	Color color1, interpolateColor, currentColor;
	Array<double> leftWeight;
	Array<double> rightWeight;
	Array<double> weight;
	double weight1;

    scanLineComputer.Init();
    scanLineComputer.Compute(p1, p2, p3);
    for(int i=scanLineComputer.ymin; i<=scanLineComputer.ymax; i++){
        // point à gauche
        rightPt = Coord2D(scanLineComputer.left.data[i],i);
        rightWeight = scanLineComputer.rightweight.data[i];
        // point à droite
        leftPt = Coord2D(scanLineComputer.right.data[i], i);
        leftWeight = scanLineComputer.leftweight.data[i];

        if(rightPt.x == leftPt.x){
            color1 = (c1*leftWeight.data[0] + c2*leftWeight.data[1] + c3*leftWeight.data[2]) *
                    pointLight.GetColor(posi1*leftWeight.data[0]+posi2*leftWeight.data[1] + posi3*leftWeight.data[2],
                                        normal1*leftWeight.data[0] + normal2*leftWeight.data[1] + normal3*leftWeight.data[2])
                    + ambientLight.ambientColor;
            SetPoint(leftPt, color1);
        }
        else{
            weight1 = 1/leftPt.Distance(rightPt);
            weight.data[0] = weight1 * (rightWeight.data[0] - leftWeight.data[0]);
            weight.data[1] = weight1 * (rightWeight.data[1] - leftWeight.data[1]);
            weight.data[2] = weight1 * (rightWeight.data[2] - leftWeight.data[2]);
            interpolatePt = posi1*weight.data[0] + posi2*weight.data[1] + posi3*weight.data[2];
            interpolateNormal = normal1*weight.data[0] + normal2*weight.data[1] + normal3*weight.data[2];
            interpolateColor = c1*weight.data[0] + c2*weight.data[1] + c3*weight.data[2];

            currentPt = leftPt;
            currentColor = c1*weight.data[0] + c2*weight.data[1] + c3*weight.data[2];
            currentNormal = normal1*weight.data[0] + normal2*weight.data[1] + normal3*weight.data[2];
            currentPos = posi1*weight.data[0] + posi2*weight.data[1] + posi3*weight.data[2];
            for(currentPt.y; currentPt.y <= rightPt.y; currentPt.y++){
                SetPoint(currentPt,
                         currentColor * pointLight.GetColor(currentPos, currentNormal)
                         + ambientLight.ambientColor);
                currentColor = currentColor + interpolateColor;
                currentNormal += interpolateNormal;
                currentPos = interpolatePt;
            }
        }
    }



}

