#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>

void Renderer::DrawFilaire()
{
	// compléter ici
    Coord3D p1, p2, p3;
    Color c1, c2, c3;
    Face f;

	// L'objet a dessiné est dans l'attribut drawable
	// on parcourt le tableau contenant la liste des faces/triangles a dessiné
	for(int i=0; i< drawable->faces.size; i++){
       f = drawable->faces.data[i];
        //coord  et couleur point 1
       p1 = drawable->points.data[f.index1];
       c1 = drawable->pointColors.data[f.index1];

       // coord  et couleur point 2
       p2 = drawable->points.data[f.index2];
       c2 = drawable->pointColors.data[f.index2];
       // coord  et couleur point 3
       p3 = drawable->points.data[f.index3];
       c3 = drawable->pointColors.data[f.index3];

//       buffer->DrawLine(p1, p2, c1, c2);
//       buffer->DrawLine(p1, p3, c1, c3);
//       buffer->DrawLine(p2, p3, c2, c3);
	}


}
void Renderer::DrawFilaireCache()
{
	// compléter ici
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
