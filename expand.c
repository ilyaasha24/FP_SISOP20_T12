//LOGIC
//1. Membaca file tiap characters
//2. Menggantikan tab dengan spasi
//3. Jika 1 spasi gacukup ya ditambah
//4. Tulis di file lain

#include "types.h"
#include "stat.h"
#include "user.h"

//pembuatan buffer
char buf[512];

//fungsi pembuatan file
void cat(int text)
{ 
  //deklarasi variabel
  int n, count = 1;
  char a[] = "\t\na";

  //apabila kata masih ada atau lebih dari nol
  while((n = read(text, buf, 1)) > 0) 
  {
    //jika kata dalam buffer sama seperti nilai dari a (tab)
    if(buf[0] == a[0])
    {
        //menggantikan tab nya menjadi spasi
        printf(1, " ");
        count++;

        //apabila tab nya tidak cukup dengan satu spasi
        while(count%8 != 1)
        {
          printf(1, " ");
          count++;
        }
        
    } 

    //jika kata dalam buffer tidak merupakan tab
    else
    {
        //melakukan penulisan sekaligus melakukan fungsi 'if' jika terjadi kesalahan penulisan
        if (write(1, buf, n) != n) 
        {
          printf(1, "cat: write error\n");
          exit();
        }
        count++;
    }

    if(buf[0] == a[1]) count = 1;
    
  }

  //jika tidak ada kata yang terdeteksi
  if(n < 0)
  {
    //terjadi kesalahan pembacaan
    printf(1, "cat: read error\n");
    exit();
  }
}

int main(int argc, char *argv[])
{
  //deklarasi variabel
  int text, i;

  //jika jumlah argumen tidak memenuhi
  if(argc <= 1)
  {
    cat(0);
    exit();
  }

  //melakukan perulangan sebanyak jumalh argumen yang diterima
  for(i = 1; i < argc; i++)
  {
    //membuka file, jika file yang bernama seperti "argumen" tidak ditemukan maka
    if((text = open(argv[i], 0)) < 0)
    {
      //terjadi kesalahan
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }

    //semisal nama file didapatkan, menjalankan fungsi cat
    cat(text);
    
    //menutup file text
    close(text);
  }
  exit();
}
