//============================================================================
// Name        : main.cpp
// Author      : Charles
// Version     : 1.2
// Copyright   : Your copyright notice
// Description : Application to manage friends expenses
//============================================================================

#include "Person.hpp"
#include "Group.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main(int argc, char **argv) {


    if(!argv[1]){ // Il n'y a pas eu d'argument lors de l'appel du programme
        cout << "Veuillez indiquer le nom du fichier � ouvrir";
        cin.get() ;
        return 1;
    }

    ifstream filecsv(argv[1]); // ouverture du fichier

    if (!filecsv){ // Le fichier demand� n'est pas trouv�
        cout << "Ouverture du fichier impossible";
        cin.get() ;
        return 2;
    }

    string temp,line;
    vector <string> tableau;

    getline(filecsv, line); // r�cupere la 1ere ligne du fichier

    stringstream ss(line);

    while(getline(ss, temp, ',')){ // d�compose les dif�rente cases de la ligne
          tableau.push_back(temp);
    }

    int aname,aphone,aexpense,agname;
    int i=0;

    for (vector<string>::iterator it = tableau.begin() ; it != tableau.end(); ++it)// Je vérifie l'ordre des éléments
            {

    	if (it->compare("Name") == 0){
    		aname = i;
        }
    	if (it->compare("Phone Number") == 0){
    		aphone = i;
        }
    	if (it->compare("Expenses") == 0){
    		aexpense = i;
        }
        if (it->compare("Group Name") == 0){
             agname = i;
        }

        i++;
       }



    vector<Group> Groups; // cr�ation du groupe de groupes


    while (1){ // tant que mon fichier .csv n'est pas fini

        vector <string> person; // stock les infos de la personne

        getline(filecsv, line); // r�cupere une ligne du fichier

        stringstream ss(line);

        if ( filecsv.eof() )
            {
                 break;
            }

        while(getline(ss, temp, ',')){ // d�compose les dif�rente cases de la ligne
              person.push_back(temp);
              }


        float expen = atof((char*)person[aexpense].c_str()); // string to float pour les d�penses

        Person aPerson(person[aname],person[aphone],expen); // cr�ation de ma personne


        bool GroupEx = 0;

        for (vector<Group>::iterator it = Groups.begin() ; it != Groups.end(); ++it)// Je test si mon groupe existe d�j�
        {
            if(person[agname].compare(it->getName()) == 0){ // Est ce que le nom du groupe correspond

                GroupEx = 1;
                //aPerson.setLink();
                it->push_back(aPerson);
                it->setNbPers(((it->getNbPers()) + 1));
                break;
            }

        }

        if (!GroupEx){ // Si le groupe n'existait pas

            Group aGroup(person[agname]); // On cr�ait le nouveau groupe
            aGroup.push_back(aPerson); // On y insert la personne
            aGroup[0].setLink(&aGroup); // On ajoute le pointeur du groupe qu'on a cr��
            Groups.push_back(aGroup); // On ajoute notre groupe � notre vecteur de groupe
        }




    }

    filecsv.close();




    /*
     *  Prepare the output
     */

    for (vector<Group>::iterator it = Groups.begin() ; it != Groups.end(); ++it)
    {
                        cout << endl;
                        cout << "Group " << it->getName() << endl;
                        cout << "Total expenses:\t\t" << it->totalExpenses() << endl;
                        cout << "Expenses per person:\t" << it->expensesPerPerson() << endl;
                        cout << endl;

                        cout << "Name\t\t" << "Phone Number\t" << "Expenses\t"
                                << "Payback\t\t" << "Group" << endl;
                        cout << "--------------------------------------------------------------------------"
                        << endl;

                        Group tmpGroup = *it;

                        for (size_t i=0; i < tmpGroup.size(); ++i) {
                                // operate the payback first
                                tmpGroup[i].operatePayback(tmpGroup.expensesPerPerson());
                                // display the values
                                cout << tmpGroup[i].getName() << "\t\t" << tmpGroup[i].getPhone()
                                        << "\t\t" << tmpGroup[i].getExpenses() << "\t\t"
                                        << fixed << setprecision (2) << tmpGroup[i].getPayback() << fixed << setprecision (0) << "\t\t" << tmpGroup.getName() << endl;//tmpGroup[i].getLink()->getName() << endl;
                        }
                        cout << endl;

    }

    cin.get() ;
    return 0;
}
