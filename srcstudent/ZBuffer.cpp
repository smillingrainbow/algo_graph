#include <ZBuffer.h>

/** Initialise le Z-Buffer (les pixels sont à une profondeur infinie initialement) */
void ZBuffer::Init()
{
    // completer ici : initialisation du buffer des profondeurs

    // initialisation de la matrice de profondeur  à l'infini si le z-buffer est activé
    double infinity = DBL_MAX;
    if(enabled){
        for(int i=0; i<depths.size; i++){
            depths.data[i].Fill(infinity);
        }
    }


}

/** Fonction permettant de déterminer si le pixel (p.x,p.y) peut être remplacé par le point p.
	 * @return true si p doit remplacer le point de même coordonnées (p.x,p.y) selon la règle du Z-buffer
	 * i.e. si p est plus proche de la caméra que le même pixel mais de profondeur depths[x][y]. */
bool ZBuffer::ReplaceCurrent(const Coord2D p)
{
    bool changePoint;
    if(enabled){
        // si le point est hors limite
        if(p.y > depths.size){
            changePoint = false;
        }
        else if(p.x > depths.data[p.y].size){
            changePoint = false;
        }

        // si le point est plus proche
        if(depths.data[p.y].data[p.x] >= p.depth){
            // mise à jour des profondeurs
            depths.data[p.y].data[p.x] = p.depth;
            changePoint = true;
        }
        else{
            changePoint = false;
        }
    }
    // si le z-buffer est désactivé on ne fait rien
    else{
        changePoint = true;
    }


    return changePoint;
}
