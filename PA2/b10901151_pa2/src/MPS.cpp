#include <iostream> 
#include <vector> 
#include <stack> 
#include <fstream>

struct chord{
    int a, b;
};  //������Ӻ��I
int num_node=0;

using namespace std;  
int main(int argc, char* argv[]){ 	
    ios_base::sync_with_stdio(0);//��J�u��
    cin.tie(0);
// ��J���q
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    fin>>num_node;
    num_node/=2; //�Pstruct chord�����c����
    chord A[num_node]; 	
    for(int i=0;i<num_node;++i){
        fin>>A[i].a>>A[i].b;
    }

    vector<int> dp(num_node,1);//�إߪ��׬�num_node��vector�A�Binitial value��1 	
    for(int i=0;i<num_node;++i){ 		
        for(int j=0;j<i;++j){
            if(max(A[j].a,A[j].b)<min(A[i].a,A[i].b)){ // �Y j-th ���� i-th���p
                dp[i]=max(dp[i],dp[j]+1); 	
            }	
        } 		 		
    }  	

    int mps_size=dp[0];
    int last; 	
    for(int i=0;i<num_node;++i){ 		
        if(dp[i]>mps_size){ 			
            mps_size=dp[i];
            last=i; 		
        } 	
    } 

    stack<int> mps; 	
    mps.push(last); 	
    int i=last-1; 	
    while(1){//�i�H���Ψϥ�for�j��A�G�ϥ�while��֥i�઺�M�M����		
        if(dp[i]==dp[last]-1){		
            if(max(A[i].a,A[i].b)<min(A[last].a,A[last].b)){
                mps.push(i); 			
                last=i; 			
                if(dp[i]==1){
                    break; 		
                }
            } 	
        }	
        i=i-1; 	
    }  	
//��X���q
    fout<<mps_size<<endl; 	
    while(!mps.empty()){ 		
        i=mps.top();
        if(A[i].a<A[i].b)   fout<<A[i].a<<" "<<A[i].b<<endl; 		
        else fout<<A[i].b<<" "<<A[i].a<<endl;
        mps.pop();
 	} 

    fin.close();
    fout.flush();
    fout.close();
    return 0;
}	