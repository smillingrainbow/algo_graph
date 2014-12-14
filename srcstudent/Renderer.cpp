#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>
#include <stdio.h>
using namespace std;

/***********************************************
* DrawFilaire :Fonction qui dessine tous les segments qui compose un objet 3D
***********************************************/
void Renderer::DrawFilaire()
{
    Color c1, c2, c3;
    Face f;
    Coord2D m1, m2, m3;

	// L'objet a dessiné est dans l'attribut drawable
	// on parcourt le tableau contenant la liste des faces/triangles a dessiné
	for(int i=0; i< drawable->faces.size; i++){

        f = drawable->faces.data[i];
        // Coordonnées et couleur point 1
        m1 = renderable.points2D.data[f.index1];

        // Coordonnées et couleur point 2
        m2 = renderable.points2D.data[f.index2];

        // Coordonnées et couleur point 3
        m3 = renderable.points2D.data[f.index3];

        // On colore selon les cas ou le kaledioscope est activé ou désactivé
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


       // On dessine les segments qui définissent les faces de l'objet
       buffer->DrawLine(m1, m2, c1, c2);
       buffer->DrawLine(m1, m3, c1, c3);
       buffer->DrawLine(m2, m3, c2, c3);
	}
}



/***********************************************
* DrawFilaireCache : Fonction qui dessine tous les segments visibles qui compose un objet 3D , par rapport à la caméra
***********************************************/
void Renderer::DrawFilaireCache()
{
    Color c1, c2, c3;
    Face f;
    Coord2D m1, m2, m3;
    int index;

	// L'objet a dessiner est dans l'attribut drawable
	// On parcourt le tableau contenant la liste des faces/triangles a dessiné
	for(int i=0; i<=(effectiveDrawable->sortedVisibleFaces.size -1); i++){

        // On récupère uniquement les faces visibles accessibles selon l'orientation de la caméra sur notre objet
        index = effectiveDrawable->sortedVisibleFaces.data[i].index;
        f = drawable->faces.data[index];

        // Coordonnées et couleur point 1
        m1 = renderable.points2D.data[f.index1];

        // Coordonnées et couleur point 2
        m2 = renderable.points2D.data[f.index2];

        // Coordonnées et couleur point 3
        m3 = renderable.points2D.data[f.index3];

         // On colore selon les cas ou le kaledioscope est activé ou désactivé
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

       // On dessine les segments qui définissent les faces de l'objet
       buffer->DrawLine(m1, m2, c1, c2);
       buffer->DrawLine(m1, m3, c1, c3);
       buffer->DrawLine(m2, m3, c2, c3);
	}
}



/***********************************************
* Fonction qui dessine un objet 3D avec des faces pleines
***********************************************/
void Renderer::DrawFacePleine()
{
    Color c1, c2, c3;
    Face f;
    Coord2D m1, m2, m3;
    int index;

	// L'objet a dessiné est dans l'attribut drawable
	// On parcourt le tableau contenant la liste des faces/triangles a dessiné
	for(int i=0; i<=(effectiveDrawable->sortedVisibleFaces.size -1); i++){

        // On se concentrera sur les faces visibles de notre objet par la caméra
        index = effectiveDrawable->sortedVisibleFaces.data[i].index;
        f = drawable->faces.data[index];

        // Coordonnées et couleur point 1
        m1 = renderable.points2D.data[f.index1];

        // Coordonnées et couleur point 2
        m2 = renderable.points2D.data[f.index2];

        // Coordonnées et couleur point 3
        m3 = renderable.points2D.data[f.index3];

         // On colore selon les cas ou le kaledioscope est activé ou désactivé
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

        // On dessine les faces en remplissant le volume de celles-ci
       buffer->DrawFilledTriangle(m1, m2, m3, c1, c2, c3);
	}
}



/***********************************************
* DrawLambert : Fonction qui dessine un objet 3D avec des faces pleines
*               Et qui applique la technique lambert pour l'éclairage de notre objet
*               ( selon la normalisation de la couleur par rapport à la moyenne des sommet d'une face )
***********************************************/
void Renderer::DrawLambert()
{
	Color c1, c2, c3;
    Face f;
    Coord2D m1, m2, m3;
    int index;
    Color light;

	// L'objet a dessiné est dans l'attribut drawable
	// on parcourt le tableau contenant la liste des faces/triangles a dessiné
	for(int i=0; i<=(effectiveDrawable->sortedVisibleFaces.size -1); i++){

         // On se concentrera sur les faces visibles de notre objet par la caméra
        index = effectiveDrawable->sortedVisibleFaces.data[i].index;
        f = drawable->faces.data[index];

        // On réalise la normalisation de la couleur par rapport à la moyenne des sommets
        light = pointLight.GetColor((effectiveDrawable->points.data[f.index1] +
                                    effectiveDrawable->points.data[f.index2] +
                                    effectiveDrawable->points.data[f.index3])*(1./3.),
                                    effectiveDrawable->faceNormals.data[index])
                                    + ambientLight.ambientColor;

          // Coordonnées et couleur point 1
        m1 = renderable.points2D.data[f.index1];

          // Coordonnées et couleur point 2
        m2 = renderable.points2D.data[f.index2];

        // Coordonnées et couleur point 3
        m3 = renderable.points2D.data[f.index3];

        // On colore selon les cas ou le kaledioscope est activé ou désactivé
        if(drawable->colorOnFace){
            c1 = drawable->faceColors.data[index] * light;
            c2 = drawable->faceColors.data[index] * light;
            c3 = drawable->faceColors.data[index] * light;
        }
        else{
            c1 = drawable->pointColors.data[f.index1] * light;
            c2 = drawable->pointColors.data[f.index2] * light;
            c3 = drawable->pointColors.data[f.index3] * light;
        }

       // On dessine les faces en remplissant le volume de celles-ci
       buffer->DrawFilledTriangle(m1, m2, m3, c1, c2, c3);
	}
}




/***********************************************
* DrawGouraud : Fonction qui dessine un objet 3D avec des faces pleines
*               Et qui applique la technique lambert pour l'éclairage de notre objet
*               ( selon la normalisation de la couleur par rapport à chaque sommets )
***********************************************/
void Renderer::DrawGouraud()
{
    Color c1, c2, c3;
    Face f;
    Coord2D m1, m2, m3;
    int index;
    Color light1, light2, light3;

	// L'objet a dessiné est dans l'attribut drawable
	// on parcourt le tableau contenant la liste des faces/triangles a dessiné
	for(int i=0; i<=(effectiveDrawable->sortedVisibleFaces.size -1);i++){

        // On se concentrera sur les faces visibles de notre objet par la caméra
        index = effectiveDrawable->sortedVisibleFaces.data[i].index;
        f = drawable->faces.data[index];

        // On réalise normalisation de la couleur par rapport à chaque sommet
        light1 = pointLight.GetColor(effectiveDrawable->points.data[f.index1],
                                    effectiveDrawable->pointNormals.data[f.index1])
                                    + ambientLight.ambientColor;
        light2 = pointLight.GetColor(effectiveDrawable->points.data[f.index2],
                                    effectiveDrawable->pointNormals.data[f.index2])
                                    + ambientLight.ambientColor;
        light3 = pointLight.GetColor(effectiveDrawable->points.data[f.index3],
                                    effectiveDrawable->pointNormals.data[f.index3])
                                    + ambientLight.ambientColor;

        // Coordonnées et couleur point 1
        m1 = renderable.points2D.data[f.index1];

        // Coordonnées et couleur point 2
        m2 = renderable.points2D.data[f.index2];

        // Coordonnées et couleur point 3
        m3 = renderable.points2D.data[f.index3];

        // On colore selon les cas ou le kaledioscope est activé ou désactivé
        if(drawable->colorOnFace){
            c1 = drawable->faceColors.data[index] * light1;
            c2 = drawable->faceColors.data[index] * light2;
            c3 = drawable->faceColors.data[index] * light3;
        }
        else{
            c1 = drawable->pointColors.data[f.index1] * light1;
            c2 = drawable->pointColors.data[f.index2] * light2;
            c3 = drawable->pointColors.data[f.index3] * light3;
        }

    // On dessine les faces en remplissant le volume de celles-ci
       buffer->DrawFilledTriangle(m1, m2, m3, c1, c2, c3);
	}
}



/***********************************************
* DrawPhong : Fonction qui dessine un objet 3D avec des faces pleines
*               Et qui applique la technique Phong pour l'éclairage de notre objet
***********************************************/
void Renderer::DrawPhong()
{
    Color c1, c2, c3;
    Face f;
    Coord2D m1, m2, m3;
    int index;

	// L'objet a dessiné est dans l'attribut drawable
	// on parcourt le tableau contenant la liste des faces/triangles a dessiné
	for(int i=0; i<=(effectiveDrawable->sortedVisibleFaces.size -1); i++){

        // On se concentrera sur les faces visibles de notre objet par la caméra
        index = effectiveDrawable->sortedVisibleFaces.data[i].index;
        f = drawable->faces.data[index];

         // Coordonnées et couleur point 1
        m1 = renderable.points2D.data[f.index1];

         // Coordonnées et couleur point 2
        m2 = renderable.points2D.data[f.index2];

         // Coordonnées et couleur point 3
        m3 = renderable.points2D.data[f.index3];

       // On colore selon les cas ou le kaledioscope est activé ou désactivé
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

        // On fait appel à la fonction Phong qui est codé dans la classe 'Buffer' avec les parammètres adéquats
        buffer->DrawPhongTriangle(m1, m2, m3,
                                  c1, c2, c3,
                                  effectiveDrawable->points.data[f.index1], effectiveDrawable->points.data[f.index2], effectiveDrawable->points.data[f.index3],
                                  effectiveDrawable->pointNormals.data[f.index1], effectiveDrawable->pointNormals.data[f.index2], effectiveDrawable->pointNormals.data[f.index3],
                                  ambientLight, pointLight);
    }
}
