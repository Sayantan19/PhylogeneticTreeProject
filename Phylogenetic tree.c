#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct treenode
{
    struct treenode *left;
    int data;
    struct treenode *right;
} node;

typedef struct sequence{
    char * seq;
    char * organism;
}data;



node *createtree(int n)
{
    node *s = (node *)malloc(sizeof(node));
    s->left = NULL;
    s->data = n;
    s->right = NULL;
    return s;
}

data * createsequence(int n)
{
    data * d = (data *)malloc(sizeof(data)*n);
    for(int i=0;i<n;i++)
    {
        d[i].seq = (char *)malloc(sizeof(char)*35000);
        d[i].organism = (char *)malloc(sizeof(char)*500000);
    }
    for(int i=0;i<n;i++)
    {
        if(i==0)
        {
            printf("Enter name of parent organism: ");
            scanf("%s",d[i].organism);
            printf("Enter nucleotide sequence of the organism: ");
            scanf("%s",d[i].seq);
        }
        else
        {
            printf("Enter name of organism %d: ",i+1);
            scanf("%s",d[i].organism);
            printf("Enter nucleotide sequence of organism %d: ",i+1);
            scanf("%s",d[i].seq);
        }
    }
    return d;
}

node *insert(node *n, int value)
{
    if (n == NULL)
        return createtree(value);
    else if (value < n->data)
        n->left = insert(n->left, value);
    else if (value > n->data)
        n->right = insert(n->right, value);
    return n;
}

void preorder(node *n,data * d)
{
    node *p = n;
    if (n)
    {
        if(n->data==0)
        printf("%s", d[n->data].organism);
        else
        printf("%s", d[n->data-1].organism);
        printf("\n");
        preorder(n->left,d);
        preorder(n->right,d);
        // printf("\n");
    }
    // printf("\n");
}

float Nucleotide_Difference_Calculator(char * sequence1,char * sequence2)
{
    int l1,l2;
    int s=0; 
    l1 = strlen(sequence1); 
    l2 = strlen(sequence2); 
    if(l1>l2)
    {
        for(int i=0;i<l2;i++)
            if(sequence1[i]!=sequence2[i])
                s++;
        s = s+(l1-l2);
    }
    else
    {
        for(int i=0;i<l1;i++)
            if(sequence1[i]!=sequence2[i])
                s++;
        s = s+(l2-l1);
    }
    return (s/(float)(strlen(sequence1)>strlen(sequence2)?strlen(sequence1):strlen(sequence2)));
}

int Smallest_Element_In_The_First_Row(float * arr,int n)
{
    int i;
    float min = arr[0];
    for(i=0;i<n;i++)
        if(arr[i]<min)
            min = arr[i];
    return i;
}

float ** create(int n)
{
    float ** arr = (float **)malloc(sizeof(float *)*n);
    for(int i=0;i<n;i++)
        arr[i] = (float *)malloc(sizeof(float)*n);
    return arr;
}

void display(float ** arr,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            printf("\t%f\t",arr[i][j]);
        printf("\n");
    }
}

float ** Graph_Updator(data * d,node * root,float ** arr,int n)
{
    float **a = create(n-1);
    if(n==1)
        return a;
    int x = Smallest_Element_In_The_First_Row(arr[0],n);
    insert(root,x);
    for(int i=0;i<n-1;i++)
    {
        if(i!=x)
            for(int j=0;j<n-1;j++)
                a[i][j] = (arr[i][j]+arr[i+1][j])/2.0;
    }
    display(a,n-1);
    printf("\n\n");
    a = Graph_Updator(d,root,a,n-1);
}
float ** Graph_Generator(node * root,data * d,int n)
{
    float ** arr = create(n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i>=j)
                arr[i][j] = 0;
            else
                arr[i][j] = Nucleotide_Difference_Calculator(d[i].seq,d[j].seq);
        }
    }
    display(arr,n);
    printf("\n\n");
    arr = Graph_Updator(d,root,arr,n);
    return arr;
    // return arr;
}


int main()
{

    data * d;
    // d[0].seq = "ATATAAATATGGGAAAGAGAATGGGGAAATTTCTACCAGTCTTCATCTCTGAGAGCAAACTTCTCTGCATCTCTTTCTCTCTTCTCTGGGCCTCCCCCAGCTCATCATGGCTCTCTGGATCCGATCACTGCCTCTTCTGGCTCTCCTTGTCTTTTCTGGCCCTGGAACCAGCTATGCAGCTGCCAACCAGCACCTCTGTGGCTCCCACTTGGTGGAGGCTCTCTACCTGGTGTGTGGAGAGCGTGGCTTCTTCTACTCCCCCAAAGCCCGACGGGATGTCGAGCAGCCCCTAGTGAGCAGTCCCTTGCGTGGCGAGGCAGGAGTGCTGCCTTTCCAGCAGGAGGAATACGAGAAAGTCAAGCGAGGGATTGTTGAGCAATGCTGCCATAACACGTGTTCCCTCTACCAACTGGAGAACTACTGCAACTAGCCAAGAAGCCGGAAGCGGGCACAGACATACACTTACTCTATCGCACCTTCAAAGCATTTGAATAAACCTTGTTGGTCTACTGGAAGACTTGTGCC";
    // d[0].organism = "NM_205222.3 Gallus gallus insulin (INS), mRNA";
    // d[1].seq = "CACCCCGACACGGCCGGCAAACAGGTCGCCATGGCCCTCTGGATGCGCCTCCTGCCCCTGCTGGCCCTGCTGGCCCTCTGGGCGCCCGCGCCCACCCGAGCCTTCGTTAACCAGCACCTGTGTGGCTCCCACCTGGTAGAGGCTCTGTACCTGGTGTGCGGGGAGCGCGGCTTCTTCTACACGCCTAAGGCCCGCCGGGAGGTGGAGGACCTGCAGGTGAGGGACGTGGAGCTGGCCGGGGCGCCTGGCGAGGGCGGCCTGCAGCCCCTGGCCCTGGAGGGGGCCCTGCAGAAGCGAGGCATCGTGGAGCAGTGCTGCACCAGCATCTGCTCCCTCTACCAGCTGGAGAATTACTGCAACTAGGGGCGCGGGGGGCAGGACGTGGCAGCACCTGCTGCAGGTCACGGTGGCCGCAAGCCTTCGGCTCTCTGCACCCCAAGTGATTCAATAAACCCTCTGAATG";
    // d[1].organism = "NM_001130093.2 Canis lupus familiaris insulin (INS), mRNA";
    // d[2].seq = "CCGATGTGCTCTGAAAGCCTGGATGCAAAAACACCTTCTCTTGTCTACCATCTCTACCATTCCTTGTCCTCTGCTGCAAGAACAGTGTGACCATGGCAGTGTGGCTCCAGGCTGGTGCTCTTTTGTTCTTGTTGGCCGTCTCCAGTGTGAACGCTAACGCAGGGGCCCCACAGCATCTGTGTGGATCTCATCTGGTCGATGCCCTCTACCTGGTCTGTGGTCCAACAGGATTCTTCTACAACCCCAAGAGAGATGTTGACCCTCTTATGGGTTTCCTTCCTCCAAAATCTGCCCAGGAAACTGAGGTGGCTGACTTTGCATTTAAAGATCATGCCGAGGTGATAAGGAAGAGAGGCATTGTGGAGCAGTGTTGCCACAAACCCTGCAGTATCTTTGAGCTGCAGAACTACTGTAACTAAAGAACCTGCACATGTCTTGTGACAACTGCCAGTGACTTTACCACCTGTTTGCACACAGGTATCATGGGAATTACGAGAACTAAACAAAAAGTATCTTTTATTTTAAAATAGTTTACTTTT";
    // d[2].organism = "KX951416.1 Labeo rohita insulin mRNA, complete cds";
    // d[3].seq = "ATGGCCCTGTGGATGCGCCTCCTGCCCCTGCTGGCGCTGCTGGCCCTCTGGGGACCTGACCCAGCCGCAGCCTTTGTGAACCAACACCTGTGCGGCTCACACCTGGTGGAAGCTCTCTACCTAGTGTGCGGGGAACGAGGCTTCTTCTACACACCCAAGACCCGCCGGGAGGCAGAGGACCTGCAGGTGGGGCAGGTGGAGCTGGGCGGGGGCCCTGGTGCAGGCAGCCTGCAGCCCTTGGCCCTGGAGGGGTCCCTGCAGAAGCGTGGCATTGTGGAACAATGCTGTACCAGCATCTGCTCCCTCTACCAGCTGGAGAACTACTGCAACTAG";
    // d[3].organism = "BT006808.1 Homo sapiens insulin mRNA, complete cds";
    // d[4].seq = "AACCCTAAGTGACCAGCTACAATCATAGACCATCAGCAAGCAGGTCATTGTTCCAACATGGCCCTGTGGATGCGCTTCCTGCCCCTGCTGGCCCTGCTCGTCCTCTGGGAGCCCAAGCCTGCCCAGGCTTTTGTCAAACAGCACCTTTGTGGTCCTCACCTGGTGGAGGCTCTGTACCTGGTGTGTGGGGAACGTGGTTTCTTCTACACACCCAAGTCCCGTCGTGAAGTGGAGGACCCGCAAGTGCCACAACTGGAGCTGGGTGGAGGCCCGGAGGCCGGGGATCTTCAGACCTTGGCACTGGAGGTTGCCCGGCAGAAGCGTGGCATTGTGGATCAGTGCTGCACCAGCATCTGCTCCCTCTACCAACTGGAGAACTACTGCAACTGAGTCCACCACTCCCCGCCCACCCCTCTGCAATGAATAAAGCCTTTGAATGAGCACCAAAAAAAAAAAAAAAAAA";
    // d[4].organism = "NM_019129.3 Rattus norvegicus insulin 1 (Ins1), mRNA";
    // d[5].seq = "AGCCCTCTGGGACCAGCTGTGTTCCCAGGCCACCGGCAAGCAGGTCCTCACCCCCCGCCATGGCCCTGTGGACGCGCCTCCTGCCCCTGCTGGCCCTGCTGGCCCTCTGGGCGCCCGCCCCGGCCCAGGCCTTCGTGAACCAGCACCTGTGCGGCTCCCACCTGGTGGAGGCGCTGTACCTGGTGTGCGGGGAGCGCGGCTTCTTCTACACGCCCAAGGCCCGTCGGGAGGCGGAGAACCCTCAGGCAGGTGCCGTGGAGCTGGGCGGAGGCCTGGGCGGCCTGCAGGCCCTGGCGCTGGAGGGGCCCCCGCAGAAGCGTGGCATCGTGGAGCAGTGCTGCACCAGCATCTGTTCCCTCTACCAGCTGGAGAACTACTGCAACTAGGCCGCCCCTGAGGGCGCCTGCTGCTCCCCGCACCCCAAAACCCAATAAA";
    // d[5].organism = "NM_001109772.1 Sus scrofa insulin (INS), mRNA";
    // d[6].seq = "AGCCCCCCGCCCTCAGGACCGGCTGCATTCGAGGCTGCCAGCAAGCAGGTCCTCGCAGCCCCGCCATGGCCCTGTGGACACGCCTGGCGCCCCTGCTGGCCCTGCTGGCGCTCTGGGCCCCCGCCCCGGCCCGCGCCTTCGTCAACCAGCATCTGTGTGGCTCCCACCTGGTGGAGGCGCTGTACCTGGTGTGCGGAGAGCGCGGCTTCTTCTACACGCCCAAGGCCCGCCGGGAGGTGGAGGGCCCCCAGGTGGGGGCGCTGGAGCTGGCCGGAGGCCCGGGCGCGGGCGGCCTGGAGGGGCCCCCGCAGAAGCGTGGCATCGTGGAGCAGTGCTGTGCCAGCGTCTGCTCGCTCTACCAGCTGGAGAACTACTGTAACTAGGCCTGCCCCCGACACCAATAAACCCCTTGACGAGCCCTGCAAAAAAAAAAA";
    // d[6].organism = "NM_173926.2 Bos taurus insulin (INS), transcript variant 1, mRNA";
    // d[7].seq = "AGCCCTCCAGGACAGGCTGCATCAGAAGAGGCCATCAAGCAGATCACTGTCCTTCTGCCATGGCCCTGTGGATGCGCCTCCTGCCCCTGCTGGTGCTGCTGGCCCTCTGGGGACCTGACCCAGCCTCGGCCTTTGTGAACCAACACCTGTGCGGCTCCCACCTGGTGGAAGCTCTCTACCTAGTGTGCGGGGAACGAGGCTTCTTCTACACACCCAAGACCCGCCGGGAGGCAGAGGACCTGCAGGTGGGGCAGGTGGAGCTGGGCGGGGGCCCTGGTGCAGGCAGCCTGCAGCCCTTGGCCCTGGAGGGGTCCCTGCAGAAGCGTGGTATCGTGGAACAATGCTGTACCAGCATCTGCTCCCTCTACCAGCTGGAGAACTACTGCAACTAGATGGAATAAAGCCCTTGAACCAGC";
    // d[7].organism = "NM_001008996.2 Pan troglodytes insulin (INS), mRNA";
    // d[8].seq = "GCATTCTGAGGCATTCTCTAACAGGTTCTCGACCCTCCGCCATGGCCCCGTGGATGCATCTCCTCACCGTGCTGGCCCTGCTGGCCCTCTGGGGACCCAACTCTGTTCAGGCCTATTCCAGCCAGCACCTGTGCGGCTCCAACCTAGTGGAGGCACTGTACATGACATGTGGACGGAGTGGCTTCTATAGACCCCACGACCGCCGAGAGCTGGAGGACCTCCAGGTGGAGCAGGCAGAACTGGGTCTGGAGGCAGGCGGCCTGCAGCCTTCGGCCCTGGAGATGATTCTGCAGAAGCGCGGCATTGTGGATCAGTGCTGTAATAACATTTGCACATTTAACCAGCTGCAGAACTACTGCAATGTCCCTTAGACACCTGCCTTGGGCCTGGCCTGCTGCTCTGCCCTGGCAACCAATAAACCCCTTGAATGAG";
    // d[8].organism = "M57671.1 Octodon degus insulin mRNA, complete cds";
    // d[9].seq = "TCATCGGCTCTGCACCATGGCCTCCCTGGCCGCGCTCCTGCCCCTGCTGGCCCTGCTGGTCCTCTGCAGACTGGATCCTGCCCAGGCCTTCGTCAACCAGCACCTGTGCGGCTCTCACCTGGTGGAGGCGCTGTACCTGGTGTGCGGGGAGCGCGGCTTTTTTTATACACCCAAGTCCCGCCGCGAGGTGGAGGAGCTGCAGGTGGGGCAGGCGGAGCTGGGCGGGGGGCCCGGCGCGGGCGGCCTGCAGCCCTCGGCGCTGGAGCTGGCCCTGCAGAAGCGCGGCATCGTGGAGCAGTGTTGCACCAGCATCTGCTCGCTCTACCAGCTGGAGAACTACTGCAACTAGGGGTGCCCCCCACCCACCCCTGCCCGCGCCCCCCACGCCCCCCGCCCTCGCCCCCACCCAATAAACCCCTCCACGCGCCCCGGG";
    // d[9].organism = "U03610.1 Oryctolagus cuniculus New Zealand White insulin mRNA, complete cds";
    int n;
    printf("Enter the number of organisms whose Phylogenetic tree is to be found out: ");
    scanf("%d",&n);
    d = createsequence(n);
    node * tree = createtree(0);
    float ** m = Graph_Generator(tree,d,n);
    printf("The lineage has been placed in Pre-Order format, i.e., Root->left->right:\n");
    preorder(tree,d);
    // printf("%f",diff);
}