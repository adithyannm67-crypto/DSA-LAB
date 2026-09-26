#include <stdio.h>
#include <string.h>

int main()
{
    char str[200], word[50], newword[50];
    char temp[500];
    int i, j, k, n = 0;
    int len, wordlen, newlen;
    int found;

    printf("ENTER STRING : ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';

    printf("WORD TO BE MODIFIED: ");
    fgets(word, sizeof(word), stdin);
    word[strcspn(word, "\n")] = '\0';

    printf("NEW WORD : ");
    fgets(newword, sizeof(newword), stdin);
    newword[strcspn(newword, "\n")] = '\0';

    len = strlen(str);
    wordlen = strlen(word);
    newlen = strlen(newword);

    i = 0;
    k = 0;

    while (i < len)
    {
        found = 1;

        if (i + wordlen > len)
        {
            found = 0;
        }
        else
        {
            for (j = 0; j < wordlen; j++)
            {
                if (str[i + j] != word[j])
                {
                    found = 0;
                    break;
                }
            }
        }

        if (found)
        {
            for (j = 0; j < newlen; j++)
            {
                temp[k++] = newword[j];
            }

            i = i + wordlen;
            n++;
        }
        else
        {
            temp[k++] = str[i];
            i++;
        }
    }

    temp[k] = '\0';

    printf("\nNEW STRING : %s", temp);
    printf("\nNO OF CHANGES : %d\n", n);

    return 0;
}
