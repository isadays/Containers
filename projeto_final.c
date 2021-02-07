/*****************************************************************************
* ARQUIVO: omp_mpiprodutoescalar600172.c
* DESCRIÇÃO :
	Este programa é uma adaptação da versão de Blaise Barney de uma versão híbrida, utilizando MPI e OpenMP, de um produto escalar. 
* REVISÃO:  14/01/21 ISABELA DIAS
* https://computing.llnl.gov/tutorials/openMP/samples/C/omp_dotprod_hybrid.c

******************************************************************************/

#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

/* Definição do tamanho dos vetores a serem utilizados e o número de threads */
#define VECLEN 1000
#define NUMTHREADS 8

int main (int argc, char* argv[])
{
int i, myid, tid, numprocs, len=VECLEN, threads=NUMTHREADS;
double *a, *b;
double mysum, allsum, sum, psum;

/* Inicialização MPI  */
MPI_Init (&argc, &argv);
MPI_Comm_size (MPI_COMM_WORLD, &numprocs);
MPI_Comm_rank (MPI_COMM_WORLD, &myid);

/* 
   Cada tarefa MPI usa OpenMP a fim de realizar o produto escalar, obtido a partir de sua soma parcial. Posteriormente, chama a função MPI_Reduce para obter a soma global.
*/
if (myid == 0)
  printf("Iniciando omp_mpiprodutoescalar600172. Usando %d tarefas...\n",numprocs);

/* Alocação dinâmica dos vetores  */
a = (double*) malloc (len*threads*sizeof(double));
b = (double*) malloc (len*threads*sizeof(double));
 
/* Inicializa os vetores para produto escalar*/
for (i=0; i<len*threads; i++) {
  a[i]=1.0;
  b[i]=a[i];
  }

/*
   Realiza o produto escalar na região paralela OpenMP com loop for com uma redução de soma
   A seguir, apresenta-se algumas informações:
     - A configuração do número de threads
     - Pega e imrpime o número de threads usadas
     - Cada thread mantém o caminho de sua soma parcial
*/

/* Inicializa a cláusula de redução OpenMP, a qual permite especificar a variável soma de thread privado que está sujeita a uma operação de redução ao final da região paralela */

sum = 0.0;

#pragma omp parallel private(i,tid,psum) num_threads(threads)
{
psum = 0.0;
tid = omp_get_thread_num();
if (tid ==0)
  {
    threads = omp_get_num_threads();
    printf("Task %d using %d threads\n",myid, threads);
  }

#pragma omp for reduction(+:sum)
  for (i=0; i<len*threads; i++)
    {
      sum += (a[i] * b[i]);
      psum = sum;
    }
printf("Tarefa %d thread %d soma parcial = %f\n",myid, tid, psum);
}


/* Imprime a tarefa de soma parcial */
mysum = sum;
printf("Tarefa %d soma parcial = %f\n",myid, mysum);

/* Depois do cálculo do produto escalar, é performada uma somatória de resultados em cada nó  */
MPI_Reduce (&mysum, &allsum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
if (myid == 0) 
  printf ("Finalizado. Versão hibrida: soma global  =  %f \n", allsum);

free (a);
free (b);
MPI_Finalize();
}   

