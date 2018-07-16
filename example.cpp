
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <gmp.h>    // gmp is included implicitly
#include <libhcs.h> // master header includes everything


using namespace std;

clock_t start,finish;
double eps;

int main(void)
{
    // initialize data structures
   	djcs_public_key *pk = djcs_init_public_key();
   	djcs_private_key *vk = djcs_init_private_key();
   	hcs_random *hr = hcs_init_random();

    // Generate a key pair with modulus of size 2048 bits
    djcs_generate_key_pair(pk, vk, hr, 2, 2048);

    


    mpz_t a, b, c;
    mpz_inits(a, b, c, NULL);

    mpz_set_ui(a, 1);
    mpz_set_ui(b, 76);
   

    hcs_reseed_random(hr);
    start=clock();

    djcs_encrypt(pk, hr, a, a,1);  // Encrypt a (= 50) and store back into a
    gmp_printf("%d\n", mpz_sizeinbase(a,2));

    finish=clock();
    eps=(double)(finish-start)/CLOCKS_PER_SEC;
    //   SIEncodingTime<<eps<<endl;
    cout<<"encrypt 1 value  takes "<<eps<<" seconds!"<<endl;

    hcs_reseed_random(hr);
    djcs_encrypt(pk, hr, b, b,1); 
   // gmp_printf("%d\n", mpz_sizeinbase(b,2));
     // Encrypt b (= 76) and store back into b
  //  gmp_printf("a = %Zd\nb = %Zd\n", a, b); // can use all gmp functions still

   // hcs_reseed_random(hr);

    start=clock();
    djcs_ee_add(pk,c,a,b,1);
   // djcs_ep_mul(pk, c, a, b,2);    // Add encrypted a and b values together into c
    finish=clock();
    eps=(double)(finish-start)/CLOCKS_PER_SEC;
    //   SIEncodingTime<<eps<<endl;
    cout<<"multiplication 2 values  takes "<<eps<<" seconds!"<<endl;



    start=clock();
    djcs_decrypt(vk, c, c,1);      // Decrypt c back into c using private key
    //gmp_printf("%d\n", mpz_sizeinbase(c,2));     // output: c = 126

  //  djcs_decrypt(vk, c, c,1);      // Decrypt c back into c using private key
    finish=clock();
    eps=(double)(finish-start)/CLOCKS_PER_SEC;
    //   SIEncodingTime<<eps<<endl;
    cout<<"decrypt 1 value  takes "<<eps<<" seconds!"<<endl;



   
 //   start=clock();
 //   djcs_decrypt(vk, c, c,1);      // Decrypt c back into c using private key
 //   finish=clock();
  //  eps=(double)(finish-start)/CLOCKS_PER_SEC;
    //   SIEncodingTime<<eps<<endl;
  //  cout<<"second decrypt 1 value  takes "<<eps<<" seconds!"<<endl;

    gmp_printf("%Zd\n", c);     // output: c = 126

    // Cleanup all data
    mpz_clears(a, b, c, NULL);
    djcs_free_public_key(pk);
    djcs_free_private_key(vk);
    hcs_free_random(hr);



	cout<<"good"<<endl;
    return 0;
}