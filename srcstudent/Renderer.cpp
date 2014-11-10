#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>
#include <stdio.h>
using namespace std;

void Renderer::DrawFilaire()
{
	// compléter ici
    Color c1, c2, c3;
    Face f;
    Coord2D m1, m2, m3;

	// L'objet a dessiné est dans l'attribut drawable
	// on parcourt le tableau contenant la liste des faces/triangles a dessiné
	for(int i=0; i< drawable->faces.size; i++){

        f = drawable->faces.data[i];
        //coord  et couleur point 1
        m1 = renderable.points2D.data[f.index1];

        // coord  et couleur point 2
        m2 = renderable.points2D.data[f.index2];

        // coord  et couleur point 3
        m3 = renderable.points2D.data[f.index3];

        if(drawable->colorOnFace){
            c1 = drawable->faceColors.data[i];
            c2 = drawable->faceColors.data[i];
            c3 = drawable->faceColors.data[i];
        }
        else{
            c1 = drawable->pointColors.data[f.index1];
            c2 = drawable->pointColors.data[f.index2];
            c3 = drawable->pointColors.data[f.index3];
        }

       buffer->DrawLine(m1, m2, c1, c2);
       buffer->DrawLine(m1, m3, c1, c3);
       buffer->DrawLine(m2, m3, c2, c3);
	}


}
void Renderer::DrawFilaireCache()
{
	// compléter ici
    Color c1, c2, c3;
    Face f;
    Coord2D m1, m2, m3;
    int index;

	// L'objet a dessiné est dans l'attribut drawable
	// on parcourt le tableau contenant la liste des faces/triangles a dessiné
	for(int i=(effectiveDrawable->sortedVisibleFaces.size -1); i>=0; i--){

        index = effectiveDrawable->sortedVisibleFaces.data[i].index;

        f = drawable->faces.data[index];
        //coord  et couleur point 1
        m1 = renderable.points2D.data[f.index1];

        // coord  et couleur point 2
        m2 = renderable.points2D.data[f.index2];

        // coord  et couleur point 3
        m3 = renderable.points2D.data[f.index3];

        if(drawable->colorOnFace){
            c1 = drawable->faceColors.data[index];
            c2 = drawable->faceColors.data[index];
            c3 = drawable->faceColors.data[index];
        }
        else{
            c1 = drawable->pointColors.data[f.index1];
            c2 = drawable->pointColors.data[f.index2];
            c3 = drawable->pointColors.data[f.index3];
        }


       buffer->DrawLine(m1, m2, c1, c2);
       buffer->DrawLine(m1, m3, c1, c3);
       buffer->DrawLine(m2, m3, c2, c3);
	}


}
void Renderer::DrawFacePleine()
{
	// compléter ici
    Color c1, c2, c3;
    Face f;
    Coord2D m1, m2, m3;
    int index;

	// L'objet a dessiné est dans l'attribut drawable
	// on parcourt le tableau contenant la liste des faces/triangles a dessiné
	for(int i=(effectiveDrawable->sortedVisibleFaces.size -1); i>=0; i--){

        index = effectiveDrawable->sortedVisibleFaces.data[i].index;

        f = drawable->faces.data[index];
        //coord  et couleur point 1
        m1 = renderable.points2D.data[f.index1];

        // coord  et couleur point 2
        m2 = renderable.points2D.data[f.index2];

        // coord  et couleur point 3
        m3 = renderable.points2D.data[f.index3];

        // Kaledioscope activé/désactivé
        if(drawable->colorOnFace){
            c1 = drawable->faceColors.data[index];
            c2 = drawable->faceColors.data[index];
            c3 = drawable->faceColors.data[index];
        }
        else{
            c1 = drawable->pointColors.data[f.index1];
            c2 = drawable->pointColors.data[f.index2];
            c3 = drawable->pointColors.data[f.index3];
        }


       buffer->DrawFilledTriangle(m1, m2, m3, c1, c2, c3);
	}



}

void Renderer::DrawLambert()
{
	// compléter ici
}
void Renderer::DrawGouraud()
{
	// compléter ici
}
void Renderer::DrawPhong()
{
	// compléter ici
}
