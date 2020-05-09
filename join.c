// LOGIC:
// 1. read text1 dan text2
// 2. get char1 dan char2 
// 3. combine char1 dan char2 

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

//pengganti fungsi length
int panjang(char *input)
{
    //deklarasi variabel
    int panjang = 0;

    //bertambah panjang selama tidak EOF (End of File)
    while(input[panjang]!='\0')
    {
        panjang++;
    }
    //pengembalian fungsi panjang/length
    return panjang;
}

int main(int argc, char *argv[])
{
	//deklarasi variabel
	int text1, text2;
	int a, b;
	char buffer1[512], buffer2[512];
	char combined[512];
	int countext1 = 0, countext2 = 0, countcombine = 0;

	//print error
	if((text1 = open(argv[1], O_RDONLY)) < 0)
	{
                //Kesalahan dalam pembacaan file pertama
		printf(1, "Failed to read files %s\n", argv[1]);
		exit();
	}
	if((text2 = open(argv[2], O_RDONLY)) < 0)
	{
		//kesalahan dalam pembacaan file kedua
		printf(1, "failed to read %s\n", argv[2]);
		exit();
	}

	//Membaca text kemudian dimasukkan kedalam buffer
	a = read(text1, buffer1, sizeof(buffer1));
	b = read(text2, buffer2, sizeof(buffer2));

	//Mendapatkan panjang dari text/buffer
	int p1, p2;
	p1 = panjang(buffer1);
	p2 = panjang(buffer2);
	// p1 = p1+1;
	// p2 = p2+1;
	// buffer1[p1]='\n';
	// buffer2[p2]='\n';

	//jika text memiliki kata
	if(a > 0 || b > 0){

		//selama buffer belum habis
		while(p1 > 0 && p2 > 0){

			//masukkan buffer (Text 1) kedalam combine selama belum terdeteksi enter
			while(buffer1[countext1] != '\n'){
				combined[countcombine] = buffer1[countext1];            
				countcombine++; countext1++;
			}

			//menambahkan spasi dan menuju ke text2
			combined[countcombine] = ' ';
			countcombine++;

			//memasukkan buffer kedua (Text 2) dalam combine selama belum terdeteksi enter
			while(buffer2[countext2] != '\n'){
				combined[countcombine] = buffer2[countext2];
				countcombine++; countext2++;
			}

			//join baris x selesai, menambahkan enter
			combined[countcombine] = buffer2[countext2];   
			// combined[countcombine] = '\n';
			countcombine++;
			countext1++;
			countext2++;

			//mengurangi buffer
			p1-=countext1;
			p2-=countext2;
		}
	}

	//menutup text
	close(text1);
	close(text2);

	//mencetak hasil dari seluruh join
	printf(1, "%s\n", combined);
	exit();
}
