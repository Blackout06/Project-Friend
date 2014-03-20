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


    /*if(!argv[1]){ // Il n'y a pas eu d'argument lors de l'appel du programme
        cout << "Veuillez indiquer le nom du fichier a ouvrir";
        cin.get() ;
        return 1;
    }*/

    ifstream filecsv("/home/charles/workspace/Friends-expenses-file/Debug/file.csv"); // ouverture du fichier

    if (!filecsv){ // Le fichier demande n'est pas trouve
        cout << "Ouverture du fichier impossible";
        cin.get() ;
        return 2;
    }

    string temp,line;
    vector <string> tableau;

    getline(filecsv, line); // recupere la 1ere ligne du fichier

    stringstream ss(line);

    while(getline(ss, temp, ',')){ // decompose les diferente cases de la ligne
          tableau.push_back(temp);
    }

    int aname,aphone,aexpense,agname;
    int i=0;

    for (vector<string>::iterator it = tableau.begin() ; it != tableau.end(); ++it)// Je verifie l'ordre des éléments
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



    vector<Group> Groups; // creation du groupe de groupes


    while (1){ // tant que mon fichier .csv n'est pas fini

        vector <string> person; // stock les infos de la personne

        getline(filecsv, line); // recupere une ligne du fichier

        stringstream ss(line);

        if ( filecsv.eof() )
            {
                 break;
            }

        while(getline(ss, temp, ',')){ // decompose les diferente cases de la ligne
              person.push_back(temp);
              }


        float expen = atof((char*)person[aexpense].c_str()); // string to float pour les depenses




        bool GroupEx = 0;

        for (vector<Group>::iterator it = Groups.begin() ; it != Groups.end(); ++it)// Je test si mon groupe existe deja
        {
            if(person[agname].compare(it->getName()) == 0){ // Est ce que le nom du groupe correspond

                GroupEx = 1;
                Person aPerson(person[aname],person[aphone],expen,&*it); // creation de ma personne
                it->push_back(aPerson);
                it->setNbPers(((it->getNbPers()) + 1));
                break;
            }

        }

        if (!GroupEx){ // Si le groupe n'existait pas

        	Person aPerson(person[aname],person[aphone],expen);
            Group aGroup(person[agname]); // On creait le nouveau groupe
            aGroup.push_back(aPerson); // On y insert la personne
            aGroup[0].setLink(&aGroup); // On ajoute le pointeur du groupe qu'on a cree
            Groups.push_back(aGroup); // On ajoute notre groupe a notre vecteur de groupe
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
                                        << fixed << setprecision (2) << tmpGroup[i].getPayback() << "\t\t" << tmpGroup[i].getLink()->getName() << endl<< fixed << setprecision (0);
                        } //tmpGroup.getName() << endl;//
                        cout << endl;

    }

    cin.get() ;
    return 0;
}
