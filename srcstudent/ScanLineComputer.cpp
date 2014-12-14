
#include <ScanLineComputer.h>
#include <Buffer.h>
#include <FastMath.h>
#include <limits.h>

/***************************************************
 * AddEdge : Fonction qui utilise la méthode de Bresenham pour calculer les points du segment [p1,p2] 
 *           et on les ajoute via la méthode AddPoint.
 * **************************************************/
void ScanLineComputer::AddEdge(const Coord2D p1, const Coord2D p2,
															 const int index1, const int index2)
{
    int y = p1.y, x = p1.x;
	int longX = p2.x - p1.x, longY = p2.y - p1.y;
    int const2 = 0, const1 = 0, critere = 0;
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
            if(y>=0 && y<height){
                AddPoint(x, y, p1, p2, index1, index2);
            }
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
            if(y>=0 && y<height){
                AddPoint(x, y, p1, p2, index1, index2);
            }
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





