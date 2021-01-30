#pragma warning (disable : 4996)
#include <string>
#include <iostream>

char* split(const char* value, int size)
{
    int stringIndex = 0;

    int resultIndex = 0;
    char* result = new char[size/2];
    while (stringIndex < size)
    {
        std::string byteStr;

        byteStr += value[stringIndex];
        byteStr += value[stringIndex + 1];

        result[resultIndex] = std::stoi(byteStr, 0, 16);
        
        stringIndex += 2;
        resultIndex++;
    }

    return result;
}

void insertCode(FILE* pointer, std::string bytesStr, int address)
{
    fseek(pointer, address, SEEK_SET);

    char* bytesArray = split(bytesStr.c_str(), bytesStr.size());

    fwrite(bytesArray, sizeof(char), bytesStr.size() / 2, pointer);
}

int main(int argc, char* argv[])
{
    if (argv[1] == NULL) 
    {
        std::cout << "Usage: [Filepath]";

        return 1;
    }

    FILE* pointerInFile = fopen(argv[1], "rb+");

    //Chama função criada.
    insertCode(pointerInFile, "E844AE0200", 0x000132D7);

    //Cria a função para não criar a tela de alerta.
    insertCode(pointerInFile, "81F960FC19007508C744240836ED4300FF25C0144400233332373732", 0x0003E120);

    //Remove codigo de verifição e função que fecha programa após 5 minutos.
    insertCode(pointerInFile, "F1F1F1F1F1", 0x00034FCF);
    insertCode(pointerInFile, "F1F1F1F1F1", 0x0000736B);

    //Bypass alerta de checksun alterado.
    insertCode(pointerInFile, "EBF5F1F1F1", 0x00012FEE);

    //Altera tamanho do jmp.
    insertCode(pointerInFile, "807DF300754B", 0x00012277);

    fclose(pointerInFile);

    return 0;
}
