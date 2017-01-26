#include "AES.h"

#include<stdio.h>

AES::AES(unsigned char* k) {
    for(int i=0;i<Nk*4;i++)
	{
		Key[i]=k[i];
	}
	KeyExpansion();
}

void AES::KeyExpansion() {
	int i,j;
	unsigned char temp[4],k;

	// The first round key is the key itself.
	for(i=0;i<Nk;i++) {
		RoundKey[i*4]=Key[i*4];
		RoundKey[i*4+1]=Key[i*4+1];
		RoundKey[i*4+2]=Key[i*4+2];
		RoundKey[i*4+3]=Key[i*4+3];
	}

	// All other round keys are found from the previous round keys.
	while (i < (Nb * (Nr+1))) {
        for(j=0;j<4;j++) {
            temp[j]=RoundKey[(i-1) * 4 + j];
        }

        if (i % Nk == 0) {
            // This function rotates the 4 bytes in a word to the left once.
			// [a0,a1,a2,a3] becomes [a1,a2,a3,a0]
			// Function RotWord()
			k = temp[0];
			temp[0] = temp[1];
			temp[1] = temp[2];
			temp[2] = temp[3];
			temp[3] = k;

			// SubWord() is a function that takes a four-byte input word and
			// applies the S-box to each of the four bytes to produce an output word.
			// Function Subword()
			temp[0]=sbox[temp[0]];
			temp[1]=sbox[temp[1]];
			temp[2]=sbox[temp[2]];
			temp[3]=sbox[temp[3]];

			temp[0] =  temp[0] ^ Rcon[i/Nk];
		}
		else if (Nk > 6 && i % Nk == 4) {
            // Function Subword()
            temp[0]=sbox[temp[0]];
			temp[1]=sbox[temp[1]];
			temp[2]=sbox[temp[2]];
			temp[3]=sbox[temp[3]];
        }
		RoundKey[i*4+0] = RoundKey[(i-Nk)*4+0] ^ temp[0];
		RoundKey[i*4+1] = RoundKey[(i-Nk)*4+1] ^ temp[1];
		RoundKey[i*4+2] = RoundKey[(i-Nk)*4+2] ^ temp[2];
		RoundKey[i*4+3] = RoundKey[(i-Nk)*4+3] ^ temp[3];
		i++;
	}
};

void AES::AddRoundKey(int round){
    int i,j;
	for(i=0;i<4;i++) {
		for(j=0;j<4;j++) {
			state[j][i] ^= RoundKey[round * Nb * 4 + i * Nb + j];
		}
	}
};

void AES::SubBytes(){
    int i,j;
	for(i=0;i<4;i++) {
		for(j=0;j<4;j++) {
			state[i][j] = sbox[(state[i][j])];
		}
	}
};

void AES::InvSubBytes(){
    int i,j;
	for(i=0;i<4;i++) {
		for(j=0;j<4;j++) {
			state[i][j] = rsbox[(state[i][j])];
		}
	}
};

void AES::ShiftRows(){
	unsigned char temp;

	// Rotate first row 1 columns to left
	temp=state[1][0];
	state[1][0]=state[1][1];
	state[1][1]=state[1][2];
	state[1][2]=state[1][3];
	state[1][3]=temp;

	// Rotate second row 2 columns to left
	temp=state[2][0];
	state[2][0]=state[2][2];
	state[2][2]=temp;

	temp=state[2][1];
	state[2][1]=state[2][3];
	state[2][3]=temp;

	// Rotate third row 3 columns to left
	temp=state[3][0];
	state[3][0]=state[3][3];
	state[3][3]=state[3][2];
	state[3][2]=state[3][1];
	state[3][1]=temp;
};

void AES::InvShiftRows(){
	unsigned char temp;

	// Rotate first row 1 columns to right
	temp=state[1][3];
	state[1][3]=state[1][2];
	state[1][2]=state[1][1];
	state[1][1]=state[1][0];
	state[1][0]=temp;

	// Rotate second row 2 columns to right
	temp=state[2][0];
	state[2][0]=state[2][2];
	state[2][2]=temp;

	temp=state[2][1];
	state[2][1]=state[2][3];
	state[2][3]=temp;

	// Rotate third row 3 columns to right
	temp=state[3][0];
	state[3][0]=state[3][1];
	state[3][1]=state[3][2];
	state[3][2]=state[3][3];
	state[3][3]=temp;
};

void AES::MixColumns(){
	int i;
	unsigned char Tmp,Tm,t;
	for(i=0;i<4;i++) {
		t=state[0][i];
		Tmp = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i] ;
		Tm = state[0][i] ^ state[1][i] ; Tm = xtime(Tm); state[0][i] ^= Tm ^ Tmp ;
		Tm = state[1][i] ^ state[2][i] ; Tm = xtime(Tm); state[1][i] ^= Tm ^ Tmp ;
		Tm = state[2][i] ^ state[3][i] ; Tm = xtime(Tm); state[2][i] ^= Tm ^ Tmp ;
		Tm = state[3][i] ^ t ; Tm = xtime(Tm); state[3][i] ^= Tm ^ Tmp ;
	}
};

void AES::InvMixColumns(){
    int i;
	unsigned char a,b,c,d;
	for(i=0;i<4;i++) {

		a = state[0][i];
		b = state[1][i];
		c = state[2][i];
		d = state[3][i];


		state[0][i] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
		state[1][i] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
		state[2][i] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
		state[3][i] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);
	}
};

void AES::Cipher(){
	int i,j,round=0;

	//Copy the input PlainText to state array.
	for(i=0;i<4;i++) {
		for(j=0;j<4;j++) {
			state[j][i] = in[i*4 + j];
		}
	}

	// Add the First round key to the state before starting the rounds.
	AddRoundKey(0);

	// There will be Nr rounds.
	// The first Nr-1 rounds are identical.
	// These Nr-1 rounds are executed in the loop below.
	for(round=1;round<Nr;round++) {
		SubBytes();
		ShiftRows();
		MixColumns();
		AddRoundKey(round);
	}

	// The last round is given below.
	// The MixColumns function is not here in the last round.
	SubBytes();
	ShiftRows();
	AddRoundKey(Nr);

	// The encryption process is over.
	// Copy the state array to output array.
	for(i=0;i<4;i++) {
		for(j=0;j<4;j++) {
			out[i*4+j]=state[j][i];
		}
	}
};

void AES::InvCipher(){
    int i,j,round=0;

	//Copy the input CipherText to state array.
	for(i=0;i<4;i++) {
		for(j=0;j<4;j++) {
			state[j][i] = in[i*4 + j];
		}
	}

	// Add the First round key to the state before starting the rounds.
	AddRoundKey(Nr);

	// There will be Nr rounds.
	// The first Nr-1 rounds are identical.
	// These Nr-1 rounds are executed in the loop below.
	for(round=Nr-1;round>0;round--) {
		InvShiftRows();
		InvSubBytes();
		AddRoundKey(round);
		InvMixColumns();
	}

	// The last round is given below.
	// The MixColumns function is not here in the last round.
	InvShiftRows();
	InvSubBytes();
	AddRoundKey(0);

	// The decryption process is over.
	// Copy the state array to output array.
	for(i=0;i<4;i++) {
		for(j=0;j<4;j++) {
			out[i*4+j]=state[j][i];
		}
	}
};

void AES::SetInput(unsigned char* input) {
    for(int i=0;i<Nk*4;i++)
	{
		in[i]=input[i];
	}
};

unsigned char *AES::GetOutput() {
    return out;
};

void AES::ChangeKey(unsigned char* newKey) {
    for(int i=0;i<Nk*4;i++)
	{
		Key[i]=newKey[i];
	}
	KeyExpansion();
};
