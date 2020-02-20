#include<bits/stdc++.h>
using namespace std;

/**
 * You are given a set of N types of rectangular 3-D boxes, where the ith box has height h, width w and length l.
 * You task is to create a stack of boxes which is as tall as possible, but you can only stack a box on top of 
 * another box if the dimensions of the 2-D base of the lower box are each strictly larger than those of the 
 * 2-D base of the higher box. Of course, you can rotate a box so that any side functions as its base.It is 
 * also allowable to use multiple instances of the same type of box. 
 * You task is to complete the function maxHeight which returns the height of the highest possible stack so formed.
 * 
*/
class box{
    public:
    int h;//height
    int w;//width
    int l;//depth
    box(){
        h = w = l = 0;
    }
    box(int h,int w,int l){
        this->h = h;
        if(w > l) swap(w,l);
        this->w = w;
        this->l = l;
    }

    int base(){
        return w*l;
    }
};


int partition(box *b,int l,int r){
    int p_base  = b[l].base();
    int i = l+1;
    int j = r;
    while(i<=j){
        while(i<=j && b[i].base() >= p_base){
            i++;
        }
        while(j>=i && b[j].base() < p_base){
            j--;
        }
        if(i < j){
            swap(b[i],b[j]);
        }
    }
    swap(b[l],b[j]);
    return j;
}

void quicksort(box *b,int l,int r){
    if(l <= r){
        int pid = partition(b,l,r);
        quicksort(b,l,pid-1);
        quicksort(b,pid+1,r);
    }
}


int maxheightBoxStack(int *height,int *width,int *length,int n){
    int total_boxes = 3*n;
    int box_id = 0;
    box b[total_boxes];
    for(int i = 0;i<n;i++){
        //rotate box to create 3 possible boxes such the (width <= length)
        b[box_id] = box(height[i],width[i],length[i]);
        b[box_id+1] = box(width[i],height[i],length[i]);
        b[box_id+2] = box(length[i],width[i],height[i]);
        box_id+=3;
    }
    //sort the boxes in the decreasing order of their base area(width * length)
    quicksort(b,0,total_boxes-1);

    int ans = 0;
    int Height[total_boxes];
    for(int i = 0;i<total_boxes;i++){
        Height[i] = b[i].h;
        for(int j = 0;j<i;j++){
            if((b[i].w < b[j].w && b[i].l < b[j].l) && (Height[i] < Height[j] + b[i].h)){
                Height[i] = b[i].h  + Height[j];
            }
        }
        ans = max(ans,Height[i]);
    }
    return ans;
}

int main(){
    //height,width and length of each box i
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int height[n];
        int width[n];
        int length[n];
        for(int i = 0;i<n;i++){
            cin>>height[i]>>width[i]>>length[i];
        }
        cout<<maxheightBoxStack(height,width,length,n)<<"\n";
    }
    return 0;
}