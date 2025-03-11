/// inf inicia en 1 menos del rango de solucion
int inf = -1, sup = k;
while(sup - inf > 1){
    int mid = (sup + inf) / 2;
    if(f(mid) > f(mid + 1)){
        sup = mid;
    }else{
        inf = mid;
    }
}
int ansBin = inf + 1;
//inf + 1 es la respuesta
