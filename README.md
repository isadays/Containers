# Containers
Projeto Final - Introdução a Computação Científica. Computação de Alto Desempenho ou  High Performance Computing (HPC), na Nuvem. Criação de Container e Job paralelo utilizando OpenMP e MPI. Para isto, utilizou-se um programa escrito em C++.


---
title: "Projeto Final : Job Paralelo"
slug: "getting-started"
excerpt: "Este projeto final é requisito da Aciepe Introdução a Computação Científica. O trabalho consistiu na criação de um \"job\" paralelo, jobu600172.sh, a ser executado no cluster da UFSCar. A aplicação alvo, projeto_final.c, escrita em código c, é o produto escalar entre matrizes utilizando MPI, com a divisão das iterações no código utilizando um for paralelo com OpenMP. O serviço remoto utilizado foi o Google Drive, que foi configurado através do comando rclone config, no ambiente ssh do Cluster."
hidden: false
createdAt: "2021-01-20T17:18:30.552Z"
updatedAt: "2021-01-20T19:09:05.771Z"
---
Seja bem vindo! Abaixo se encontra a tabela para identificação dos arquivos anexados à esta pasta.
[block:parameters]
{
  "data": {
    "h-0": "Arquivo",
    "h-1": "Descrição",
    "0-0": "projeto_final.c",
    "0-1": "Este programa escrito em linguagem c, utiliza MPI e OpenMP, para calcular um produto escalar.",
    "1-0": "jobu600172.sh",
    "1-1": "Job paralelo a ser executado no cluster da Ufscar.",
    "2-0": "Singularity",
    "2-1": "Recipe para a criação do Container .",
    "3-0": "2817.out",
    "3-1": "Arquivo de saída obtido após submissão do job no Cluster."
  },
  "cols": 2,
  "rows": 4
}
[/block]

[block:api-header]
{
  "title": "Tutorial para execução do Job no Cluster"
}
[/block]

[block:api-header]
{
  "title": "A Criação do Container"
}
[/block]
Para a execução de nosso job no Cluster, é essencial que o container já esteja criado, e alocado em uma pasta no ambiente remoto. Além disso, o container deve ser configurado para executar o programa em paralelo. Para criar o container, basta utilizar a "receita" contida na pasta, a qual está nomeada por Singularity. Para isto executa-se o comando no ambiente da máquina local:
[block:code]
{
  "codes": [
    {
      "code": "$ sudo singularity build Singularity.simg Singularity",
      "language": "text"
    }
  ]
}
[/block]
Após a criação deste container, Singularity.simg, deve ser feito o seu upload no serviço remoto, em um caminho tal que conste posteriormente em nosso job. Por exemplo, para a execução deste job, utilizou-se o caminho hpc/containers/ .
[block:api-header]
{
  "title": "Caminhos"
}
[/block]

[block:callout]
{
  "type": "info",
  "title": "Criação de Pastas no Google Drive ou outro serviço remoto",
  "body": "É importante a criação de caminhos corretos para o Google Drive, isto porque os arquivos de hpc/input devem constar na pasta input e o container deve existir no caminho hpc/containers para que se faça uma cópia do container para execução do job. Ademais, o arquivo de saída é enviado ao caminho hpc/output. Não importa a denominação das pastas, deste que os caminhos no serviço remoto e local estejam corretos no job."
}
[/block]
Faz-se necessário para a execução do job que o usuário tenha acesso ao cluster. Isto se dará através *do* comando;
[block:code]
{
  "codes": [
    {
      "code": "$ ssh u<numeroufscar>@openhpc.ufscar.br",
      "language": "text"
    }
  ]
}
[/block]
Agora, com o acesso **permitido** ao Cluster, criaremos um job com extensão .sh , de acordo com o padrão sugerido e também sob vista dos recursos utilizados pelo programa a ser executado, através do comando:
[block:code]
{
  "codes": [
    {
      "code": "$ nano job<usuario>.sh",
      "language": "text"
    }
  ]
}
[/block]
Uma outra maneira é enviarmos o arquivo do job, em nossa máquina local, para o nosso ambiente ssh,  desta forma, não precisaremos criar um novo arquivo, e sim utilizar este mesmo. Isto é feito através do comando:
[block:code]
{
  "codes": [
    {
      "code": "$ scp <arquivo_job> u<nro_ufscar>@openhpc.ufscar.br:~/",
      "language": "text"
    }
  ]
}
[/block]
Antes de mais nada, é essencial checar se os caminhos estão corretos e se os arquivos de input estão contidos nos devidos caminhos.
[block:callout]
{
  "type": "info",
  "title": "Observação sobre os Caminhos no Job",
  "body": "service=<perfil_remoto>                             # Nome do perfil remoto no rclone\n\nremote_in=<caminho_pasta_servico_remoto_input>                        # Pasta no serviço remoto para input\n\nremote_out=<<caminho_pasta_servico_remoto_output>                      # Pasta no serviço remoto para output\n\nremote_sing=hpc/containers                  # Pasta no serviço remoto para os containers\n\ncontainer_in=/opt/input                     # Pasta no cluster para input\n\ncontainer_out=/opt/output                   # Pasta no cluster para output\n\nlocal_sing=.                                # Pasta local para o container singularity\n\nlocal_job=\"/scratch/job.${SLURM_JOB_ID}\"   # Pasta temporária local\n\nlocal_in=\"${local_job}/input/\"              # Pasta local para arquivos de entrada\n\nlocal_out=\"${local_job}/output/\"            # Pasta local para arquivos de saída"
}
[/block]
Por fim, executamos o nosso job através do comando:
[block:code]
{
  "codes": [
    {
      "code": "$ sbatch  job600172.sh",
      "language": "text"
    }
  ]
}
[/block]
É esperado que após a execução deste comando, apareça a seguinte mensagem na tela:
[block:code]
{
  "codes": [
    {
      "code": "Submitted batch job <id_job>",
      "language": "text"
    }
  ]
}
[/block]

[block:api-header]
{
  "title": "Por fim..."
}
[/block]
Uma vez submetido um job para a fila, podemos verificar o
status deste , através do comando
[block:code]
{
  "codes": [
    {
      "code": "$ squeue",
      "language": "text"
    }
  ]
}
[/block]

[block:api-header]
{
  "title": "Arquivo de Saída"
}
[/block]
O arquivo de saída está contido na devida pasta do serviço remoto, tal como mostra a figura
[block:image]
{
  "images": [
    {
      "image": [
        "https://files.readme.io/e7ffcd3-Captura_de_tela_de_2021-01-20_15-49-01.png",
        "Captura de tela de 2021-01-20 15-49-01.png",
        1001,
        608,
        "#fcfdfe"
      ]
    }
  ]
}
[/block]
