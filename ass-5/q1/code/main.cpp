#include <iostream>

using namespace std;
///Functionto to add Equation
void addEq(int eq1[],int eq2[],int n1,int n2);
///Function to multiply Equation
void mulEq(int eq1[],int eq2[],int n1,int n2);
int main()
{
    int n1,n2;
    cout<<"No of entries in first equation"<<endl;
    cin>>n1;
    int eq1[n1];
    for(int i=0;i<n1;i++){
        cout<<"Coefficient corresponding to power of X "<<i<<endl;
        cin>>eq1[i];
    }
    cout<<"No of entries in second equation"<<endl;
    cin>>n2;
    int eq2[n2];
    for(int i=0;i<n2;i++){
        cout<<"Coefficient corresponding to power of X "<<i<<endl;
        cin>>eq2[i];
    }
    addEq(eq1,eq2,n1,n2);
    cout << "Hello world!" << endl;
    mulEq(eq1,eq2,n1,n2);
    return 0;
}

void addEq(int eq1[],int eq2[],int n1,int n2){
    cout<<"Power of coefficient"<<"          "<<"Value of coefficient"<<endl;
    if(n1>n2){
        for(int i=0;i<n2;i++)
            cout<<"        "<<i<<"                            "<<eq1[i]+eq2[i]<<endl;
        for(int i=n2;i<n1;i++)
            cout<<"        "<<i<<"                            "<<eq1[i]<<endl;
    }
        else{
            for(int i=0;i<n1;i++)
            cout<<"        "<<i<<"                            "<<eq1[i]+eq2[i]<<endl;
            for(int i=n1;i<n2;i++)
            cout<<"        "<<i<<"                            "<<eq2[i]<<endl;
    }

}

void mulEq(int eq1[],int eq2[],int n1,int n2){
    cout<<"Power of coefficient"<<"          "<<"Value of coefficient"<<endl;
    int n3 = n1+n2-1;
    cout<<n3<<endl;
    int eq3[n3];
    for(int i=0;i<n3;i++)
        eq3[i]=0;
    for(int i=0;i<n3;i++){
        for(int j=0;j<n1;j++){
            for(int k=0;k<n2;k++){
                if(i==(j+k))
                    eq3[i]+=eq1[j]*eq2[k];
            }
        }
        //cout<<"        "<<i<<"                            "<<eq3[i]<<endl;
    }
    for(int i=0;i<n3;i++)
        cout<<"        "<<i<<"                            "<<eq3[i]<<endl;

    cout << "Hello world!" << endl;
}
