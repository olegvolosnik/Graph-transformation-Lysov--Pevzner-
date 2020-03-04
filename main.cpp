#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <bits/stdc++.h>
//#include <wingdi.h>

using namespace std;


int nr_vert=0;
int matrix[50][50];   //creating zero-MATRIX
int adjointMatrix[50][50];
int doAdjoint = 0;

int transTab[50][2];
int maxNum;

void ifAdjoing1Graph(){
    int x=0;
    for(int i=0; i<nr_vert;i++)
        for(int j=0; j<nr_vert;j++){
            if(matrix[i][j]>1){
                cout<<"I = "<<i+1<<" J "<<j+1<<endl;
                cout<<"Graph is not Adjoint 1 => multigraph"<<endl;    i=j=nr_vert;    x++;}
        }
    if(x==0){
        cout<<"Graph is Adjoint 1 => ! multigraph"<<endl;
        doAdjoint++;
    }
}

void ifAdjoint2Graph(){
    //∀ (x,y ∈ V)   N+(x) ∩ N+(y) ≠ ∅ ⇒ N+(x) = N+(y)
    int x=0, notEqual=0, equal=0;
    for(int i=0;i<nr_vert;i++){
        for(int j=0;j<nr_vert;j++) {
            for (int k = 0; k < nr_vert; k++) {
                //i - vertex X
                //j - vertex Y
                //k - column number for X and Y
                if ((matrix[i][k] == matrix[j][k])&&(i!=j)){
                    if(matrix[i][k] != 0) {
                        equal++;
                        //cout << "\n k = " << k;//TEST
                    }}
                else {
                    notEqual++;
                    //cout << "\tnotEqual  " << notEqual;//TEST
                }
            }
            if((notEqual != nr_vert-1)&&(notEqual != 0)&&(equal > 0)){
                cout<<"Graph is not Adjoint 2 => ! [forALL(x,y in V) N+(x)/\\X+(y) != 0 => N+(x) == N+(y)]"<<endl;
                //cout<<"i="<<i<<" j="<<j<<" notEqual="<<notEqual<<" equal="<<equal<<endl;//TEST
                i=j=nr_vert; x++;
            }
            notEqual=0;
            equal=0;
        }
    }
    if(x==0){
        cout<<"Graph is Adjoint 2 => [forALL(x,y in V) N+(x)/\\X+(y) != 0 => N+(x) == N+(y)]"<<endl;
        doAdjoint++;
    }
}

void ifLinear(){
    int x=0;
    for(int i=0;i<nr_vert;i++){
        for(int j=0;j<nr_vert;j++){
            for(int k=0;k<nr_vert;k++){
                for(int l=0;l<nr_vert;l++){
                    if((matrix[i][k]==1)&&(i!=j)&&(i!=l)&&(i!=k)&&(j!=k)&&(j!=l)&&(k!=l))//TODO: add-> &&(i!=k)&&(i!=l)&&(j!=k)&&(j!=l)??
                        if(matrix[i][l]==1)
                            if(matrix[k][j]==1)
                                if(matrix[l][j]==1){
                                    x = 1;
                                    //cout<<" \n matrix[i][k] = "<<matrix[i][k]<<"\n matrix[i][l] = "<<matrix[i][l];
                                    //сout<<" \n matrix[k][j] = "<<matrix[k][j]<<"\n matrix[l][j] = "<<matrix[l][j];
                                    //cout<<"\n i="<<i<<" j="<<j<<" k="<<k<<" l="<<l;
                                    i=j=k=l=nr_vert;
                                    //cout<<"\nOption 1 => NOT_LINEAR\n";
                                } // 1 option to be notLinear TODO: probably fixed
                }
                if((i!=j)&&(i!=k)&&(j!=k))
                    if(matrix[i][j]==1)
                        if(matrix[j][i]==1)
                            if(matrix[j][k]==1)
                                if(matrix[k][j]==1){
                                    cout<<"I = "<<i<<" J = "<<j<<" K = "<<k<<endl;
                                    cout<<matrix[i][j]<<" "<<matrix[j][i]<<" "<<matrix[j][k]<<" "<<matrix[k][j]<<endl;
                                    i=j=k=nr_vert;   x = 1;
                                    //cout<<"Option 2 => NOT_LINEAR\n";
                            } // 2 option to be notLinear
            }
            if(i!=j)
                if(matrix[i][j]==1)
                    if(matrix[i][i]==1)
                        if(matrix[j][i]==1)
                            if(matrix[j][j]==1){
                                i=j=nr_vert;
                                x = 1;
                                //cout<<"\nOption 3 => NOT_LINEAR\n";
                            } // 3 option to be notLinear
        }
    }
    if(x==0)
        cout<<"Graph is linear"<<endl;
    else
        cout<<"Graph is not linear"<<endl;
}

void transformation(){
    int x=0;
    for(int i =0; i<nr_vert; i++){
        for(int j=0; j<nr_vert; j++){
            if(matrix[i][j] == 1) {
                x=transTab[j][0];
                transTab[j][0] = transTab[i][1];
                //cout<<"transTab["<<j<<"][0] = "<<transTab[j][0]<<endl;//TEST
                for(int k=0; k<nr_vert; k++){
                    if(transTab[k][0]==x)
                        {transTab[k][0] = transTab[i][1];}
                    if(transTab[k][1]==x)
                        {transTab[k][1] = transTab[i][1];}
                }
            }
        }
    }

    for (int i = 0; i < nr_vert; i++) {
        cout << "transTab[" << i << "][0] transTab[" << i << "][1] = "<<transTab[i][0]<<"  "<<transTab[i][1]<< endl;
    }



    int minFree=1;
    maxNum=2;

    //cout<<transTab[3][0]<<"\t\t TEST OF SORT FUNCTION";

    while(minFree < maxNum) {
        maxNum=2;

        for(int i=0; i<nr_vert; i++) {


            if (transTab[i][0] >= transTab[i][1]) {
                if (transTab[i][0] > maxNum)
                    maxNum = transTab[i][0];
            }
            else {
                if (transTab[i][1] > maxNum)
                    maxNum = transTab[i][1];
            }


            for(int j=0; j<nr_vert; j++)
                if ((minFree == transTab[j][0]) || (minFree == transTab[j][1]))
                    minFree++;

        }

        if(minFree >= maxNum)
            break;
        //SWAP
        for (int k = 0; k < nr_vert; k++) {
            if (transTab[k][0] == maxNum)
                transTab[k][0] = minFree;
            if (transTab[k][1] == maxNum)
                transTab[k][1] = minFree;
        }

    }


    //Implementing matrix adjoint
    for(int i=0;i<nr_vert;i++){
        adjointMatrix[transTab[i][0]-1][transTab[i][1]-1] = adjointMatrix[transTab[i][0]-1][transTab[i][1]-1] + 1;
    }

}

void outputToFile(){
    ofstream output("newGraph.txt");
    output<<maxNum<<endl;

    for(int i=0;i<maxNum;i++){
        output<<i+1<<": ";
        for(int j=0;j<maxNum;j++) {
            if (adjointMatrix[i][j] >= 1 )
                for (int k = 0; k < adjointMatrix[i][j]; k++)
                    output << j + 1 << " ";
        }
        output<<";"<<endl;
    }
    output.close();
}




int main()
{
    string lineA;
    fstream file;

    file.open("Graph.txt", ios::in);
    if(file.good() == true)
    {
        string x;
        getline(file,x);
        nr_vert = stoi(x);
        cout<<nr_vert<<" - nr_vert"<<endl;

        for(int i=0;i<nr_vert;i++)
            for(int j=0;j<nr_vert;j++) {
                matrix[i][j] = 0;         //write zero's to MATRIX
                adjointMatrix[i][j] = 0;  //write zero's to adjoint MATRIX
            }

        int intA, intB;
        while(!file.eof())
        {
           //getline(file, lineA, ':');
            //getline(file, lineB);

            while(file>>lineA){
                intA=atoi(lineA.c_str())-1;
                //file>>lineA;
                while(lineA != ";"){
                    file>>lineA;
                    if(lineA == ";")
                        break;
                    else{
                        intB = atoi(lineA.c_str())-1;
                        matrix[intA][intB]=matrix[intA][intB]+1;
                        //cout<<"  "<<intB+1;
                    }
                }
                //cout<<endl;
            }
        }
    }
        file.close();

        cout << "\nMatrix " << endl;
        for (int i = 0; i < nr_vert; i++) {
            for (int j = 0; j < nr_vert; j++)
                cout << matrix[i][j] << " ";    //printing matrix
                cout << endl;
            }

        int j=0; //FILL IN TRANS_TAB
        for(int i=0; i<nr_vert;i++){
            transTab[i][0]=j+1;
            transTab[i][1]=j+2;
            //cout<<"transTab["<<i<<"][0] = "<<transTab[i][0]<<"\t"<<"transTab["<<i<<"][1] = "<<transTab[i][1]<<endl;
            j=j+2;
        }

        ifAdjoing1Graph();
        ifAdjoint2Graph();


        if(doAdjoint>=2) {
            if(doAdjoint>=2){
                ifLinear();
                transformation();
            }
            //below to show adjoint matrix and trans_tab after Sex Reassignment Surgery
            cout<<endl;
            for (int i = 0; i < nr_vert; i++) {
                cout << "transTab[" << i << "][0] transTab[" << i << "][1] = "<<transTab[i][0]<<"  "<<transTab[i][1]<< endl;
            }

            cout << "\nMatrix Adjoint " << endl;
            for (int i = 0; i < maxNum+1; i++) {
                for (int j = 0; j < maxNum+1; j++)
                    cout <<adjointMatrix[i][j] << " ";    //printing matrix adjoint
                cout << endl;
            }

            outputToFile();
        }
    return 0;
}
