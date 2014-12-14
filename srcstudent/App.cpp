#include <App.h>
#include <MainFrame.h>
#include <Config.h>
#include <locale.h>

#include <Drawable.h>

IMPLEMENT_APP(App);

const wxString StudentsNames = wxT("Maxime Facomprez & Natacha Marlio-Marette");

bool App::OnInit()
{
	//Exception::activateDebugHelper();

	// On initialise les gestionnaire de format d'images
	wxInitAllImageHandlers();
	// On initialise le générateur de nombre aléatoire
	srand( (unsigned) time(NULL));
	// On force la locale à "C" (anglais ansi)
	setlocale(LC_NUMERIC, "C");

	// On crée la fenêtre principale
	MainFrame * mf = new MainFrame(true);
	// On affiche la fenêtre principale
	mf->Show();
	// On retourne true pour indiquer que tout c'est bien déroulé
	return true;
}
