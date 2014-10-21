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
}

void Buffer::DrawPhongTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3,
		const Coord3D posi1, const Coord3D posi2, const Coord3D posi3,
		const Coord3D normal1, const Coord3D normal2, const Coord3D normal3,
		const AmbientLight & ambientLight, const PointLight & pointLight)
{
	// compléter ici
}

