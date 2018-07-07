# Reverse matrix

General algorithm sound like *"reverse matrix = multiplication inverse determinant and transposition matrix algebraics additions"*

![ALT-Gaus](http://www.calend.ru/img/content_events/i0/392.jpg "Gauss")

#### So, my algorithm consist of
1. Find determinant (here we have limitation because in the final formula we shoul use inverse determinant that means that it can't be zero. **If determinant=0, impossible find reverse matrix.**)I have made it by Gauss method. (O(n^3+n))
2. Find minor matrix. This step the hardest. Because u need find a lot of determinants(size*size) *(O(n^2(n^2+n^3+n)+n^2+n))* 
3. Find a algebraics additions *(O(n^2))*
4. Transposition *(O(n^2))*
5. multiplication inverse determinant and transposition matrix algebraics additions *(O(n^2))*

The final big O notation is O(n^6+n^4+2n^3+5n^2+2n).

More about this algorithm you can read on [this site.](http://mathprofi.ru/kak_naiti_obratnuyu_matricu.html)

## Recommendation and rules for using

* You should enter one or two arguments. 

* First argument it is a size of matrix which you want to reverse. *Matrix size can be from 2 to 34.*

* In normal mode as result  you can see only time work. If you want to see entered and reverse matrix, you should enter anything as second argument.

* If smth wrong, you will see short information about error.
