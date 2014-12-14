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
    double depth;
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

            depth = (1/(wa+ wb)) * (wa*p1.depth + wb*p2.depth);
            SetPoint(Coord2D(x, y, depth), c);
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

            depth = (1/(wa+ wb)) * (wa*p1.depth + wb*p2.depth);

            SetPoint(Coord2D(x, y, depth), c);
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
    // dession des contours
    DrawLine(p1, p2, c1, c2);
    DrawLine(p1, p3, c1, c3);
    DrawLine(p2, p3, c2, c3);

}

void Buffer::DrawPhongTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3,
		const Coord3D posi1, const Coord3D posi2, const Coord3D posi3,
		const Coord3D normal1, const Coord3D normal2, const Coord3D normal3,
		const AmbientLight & ambientLight, const PointLight & pointLight)
{
	// compléter ici
    Coord2D rightPt, leftPt, currentPt;
    Coord3D currentNormal, currentPos;
	Color currentColor;
	Array<double> leftWeight;
	Array<double> rightWeight;
	Coord3D ptInterpolateLeft, ptInterpolateRight, normalInterpolateLeft, normalInterpolateRight;
	Color colorRight, colorLeft;
    scanLineComputer.Init();
    scanLineComputer.Compute(p1, p2, p3);

    for(int i=scanLineComputer.ymin; i<=scanLineComputer.ymax; i++){
        // point à gauche
        rightPt = Coord2D(scanLineComputer.right.data[i],i);
        rightWeight = scanLineComputer.rightweight.data[i];
        // point à droite
        leftPt = Coord2D(scanLineComputer.left.data[i], i);
        leftWeight = scanLineComputer.leftweight.data[i];

        colorRight = (c1*rightWeight.data[0] + c2*rightWeight.data[1] + c3*rightWeight.data[2])
                        * (1/(rightWeight.data[0]+ rightWeight.data[1] + rightWeight.data[2]));

        colorLeft = (c1*leftWeight.data[0] + c2*leftWeight.data[1] + c3*leftWeight.data[2])
                     * (1/(leftWeight.data[0]+ leftWeight.data[1] + leftWeight.data[2]));

        ptInterpolateLeft = (posi1*leftWeight.data[0]+ posi2*leftWeight.data[1] + posi3*leftWeight.data[2])
                                * (1/(leftWeight.data[0]+ leftWeight.data[1] + leftWeight.data[2]));

        ptInterpolateRight = (posi1*rightWeight.data[0]+ posi2*rightWeight.data[1] + posi3*rightWeight.data[2])
                                * (1/(rightWeight.data[0]+ rightWeight.data[1] + rightWeight.data[2]));

        normalInterpolateLeft = (normal1*leftWeight.data[0] + normal2*leftWeight.data[1] + normal3*leftWeight.data[2])
                                * (1/(leftWeight.data[0]+ leftWeight.data[1] + leftWeight.data[2]));

        normalInterpolateRight = (normal1*rightWeight.data[0] + normal2*rightWeight.data[1] + normal3*rightWeight.data[2])
                                    * (1/(rightWeight.data[0]+ rightWeight.data[1] + rightWeight.data[2]));

        for(int i = leftPt.x; i <= rightPt.x; i++){
            double wa = 1 - (leftPt.Distance(currentPt) / leftPt.Distance(rightPt));
            double wb = 1- wa;

            currentColor.red = (1/(wa+ wb)) * (wa*colorLeft.red + wb*colorRight.red);
            currentColor.green = (1/(wa+ wb)) * (wa*colorLeft.green + wb*colorRight.green);
            currentColor.blue = (1/(wa+ wb)) * (wa*colorLeft.blue + wb*colorRight.blue);

            currentPos.x = (1/(wa+ wb)) * (wa*ptInterpolateLeft.x + wb*ptInterpolateRight.x);
            currentPos.y = (1/(wa+ wb)) * (wa*ptInterpolateLeft.y + wb*ptInterpolateRight.y);
            currentPos.z = (1/(wa+ wb)) * (wa*ptInterpolateLeft.z + wb*ptInterpolateRight.z);

            currentNormal.x = (1/(wa+ wb)) * (wa*normalInterpolateLeft.x + wb*normalInterpolateRight.x);
            currentNormal.y = (1/(wa+ wb)) * (wa*normalInterpolateLeft.y + wb*normalInterpolateRight.y);
            currentNormal.z = (1/(wa+ wb)) * (wa*normalInterpolateLeft.z + wb*normalInterpolateRight.z);

            currentPt.x = i ;
            currentPt.y = leftPt.y;

            SetPoint(currentPt,
                     currentColor * (pointLight.GetColor(currentPos, currentNormal)+ ambientLight.ambientColor));
            currentPt.x = i;
        }
        SetPoint(rightPt, colorRight * (pointLight.GetColor(ptInterpolateRight, normalInterpolateRight)+ambientLight.ambientColor));
        SetPoint(leftPt, colorLeft * (pointLight.GetColor(ptInterpolateLeft, normalInterpolateLeft)+ambientLight.ambientColor));
    }



}

