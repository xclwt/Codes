int rand47(){
    int x = 1222;
    while(x > 1221){
        x = rand35() + rand35() * 35;
    }
    
    return x % 47;
}
