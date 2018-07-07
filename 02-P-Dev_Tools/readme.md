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
