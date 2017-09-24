const LL mo=998244353;
const LL G=3;
void NTT(vector<LL>&num,int len,int ty){
    for(int i=1,j=0;i<len-1;i++){
        for(int k=len;j^=k>>=1,~j&k;);
        if(i<j)
            swap(num[i],num[j]);
    }
    LL p0;
    for(int h=0;(1<<h)<len;h++){
        int step=1<<h,step2=step<<1;
        if(ty==1)
            p0=pw(G,(mo-1)/step2,mo);
        else
            p0=pw(G,mo-1-(mo-1)/step2,mo);
        for(int i=0;i<len;i+=step2){
            LL p=1;
            for(int j=0;j<step;j++){
                LL &x=num[i+j+step];
                LL &y=num[i+j];
                LL d=p*x%mo;
                x=(y-d+mo)%mo;
                y=(y+d+mo)%mo;
                p=p*p0%mo;
            }
        }
    }
    if(ty==-1)
        for(int i=0;i<len;i++)
            num[i]=num[i]*pw(len,mo-2,mo)%mo;
}
vector<LL> mul(vector<LL>a,vector<LL>b){
    int len=a.size()+b.size();
    while((len&-len)!=len)len++;
    while(a.size()<len)a.push_back(0);
    while(b.size()<len)b.push_back(0);
    NTT(a,len,1);
    NTT(b,len,1);
    vector<LL>ans(len);
    for(int i=0;i<len;i++)
        ans[i]=a[i]*b[i]%mo;
    NTT(ans,len,-1);
    return ans;
}


