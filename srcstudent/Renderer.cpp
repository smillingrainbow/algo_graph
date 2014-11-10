#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>
#include <stdio.h>
using namespace std;

void Renderer::DrawFilaire()
{
	// compléter ici
    Coord3D p1, p2, p3;
    Color c1, c2, c3;
    Face f;
    Coord2D m1, m2, m3;

	// L'objet a dessiné est dans l'attribut drawable
	// on parcourt le tableau contenant la liste des faces/triangles a dessiné
	for(int i=0; i< drawable->faces.size; i++){
        f = drawable->faces.data[i];
        //coord  et couleur point 1
//        p1 = drawable->points.data[f.index1];
        c1 = drawable->pointColors.data[f.index1];
        m1 = renderable.points2D.data[f.index1];
//        m1.x = p1.x;
//        m1.y = p1.y;

        // coord  et couleur point 2
//        p2 = drawable->points.data[f.index2];
        c2 = drawable->pointColors.data[f.index2];
        m2 = renderable.points2D.data[f.index2];
//        m2.x = p2.x;
//        m2.y = p2.y;

        // coord  et couleur point 3
//        p3 = drawable->points.data[f.index3];
        c3 = drawable->pointColors.data[f.index3];
        m3 = renderable.points2D.data[f.index3];
//        m3.x = p3.x;
//        m3.y = p3.y;


       buffer->DrawLine(m1, m2, c1, c2);
       buffer->DrawLine(m1, m3, c1, c3);
       buffer->DrawLine(m2, m3, c2, c3);
	}


}
void Renderer::DrawFilaireCache()
{
	// compléter ici
    Coord3D p1, p2, p3;
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
        //p1 = drawable->points.data[f.index1];
        c1 = drawable->pointColors.data[f.index1];
        m1 = renderable.points2D.data[f.index1];
        //m1.x = p1.x;
        //m1.y = p1.y;

        // coord  et couleur point 2
        //p2 = drawable->points.data[f.index2];
        c2 = drawable->pointColors.data[f.index2];
        m2 = renderable.points2D.data[f.index2];
        //m2.x = p2.x;
        //m2.y = p2.y;

        // coord  et couleur point 3
        //p3 = drawable->points.data[f.index3];
        c3 = drawable->pointColors.data[f.index3];
        m3 = renderable.points2D.data[f.index3];
        //m3.x = p3.x;
        //m3.y = p3.y;


       buffer->DrawLine(m1, m2, c1, c2);
       buffer->DrawLine(m1, m3, c1, c3);
       buffer->DrawLine(m2, m3, c2, c3);
	}


}
void Renderer::DrawFacePleine()
{
	// compléter ici
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
