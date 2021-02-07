#!/bin/bash
#SBATCH -J projeto_final            # Identificação do job
#SBATCH -o %j.out                    # Nome do arquivo de saída padrão (%j = ID do JOB)
#SBATCH --error=err.txt
#SBATCH -n 100
#SBATCH -t 00:20:00           # Tempo de execução (hh:mm:ss) 00:20:00
#SBATCH --mail-user=isabeladias@estudante.ufscar.br
#SBATCH --mail-type=ALL

service=cloudc                               # Nome do perfil remoto no rclone
remote_in=hpc/input                         # Pasta no serviço remoto para input
remote_out=hpc/output                       # Pasta no serviço remoto para output
remote_sing=hpc/containers                  # Pasta no serviço remoto para os containers
container_in=/opt/input                     # Pasta no cluster para input
container_out=/opt/output                   # Pasta no cluster para output
local_sing=.                                # Pasta local para o container singularity
local_job="/scratch/job.${SLURM_JOB_ID}"   # Pasta temporária local
local_in="${local_job}/input/"              # Pasta local para arquivos de entrada
local_out="${local_job}/output/"            # Pasta local para arquivos de saída

function clean_job() {
  echo "Limpando ambiente..."
  rm -rf "${local_job}"
}
trap clean_job EXIT HUP INT TERM ERR

set -eE

umask 077

# Define o arquivo a ser copiado como o mais recente na pasta especificada
sing=$(rclone lsf --max-depth 0 "${service}:${remote_sing}/" --files-only --format "tp" | grep Sin$
sing=${sing:20}

echo "Copiando container..."
rclone copyto "${service}:${remote_sing}/${sing}" "${local_sing}/Singularity.simg"

echo "Criando pastas temporárias..."
mkdir -p "${local_in}"
mkdir -p "${local_out}"

echo "Copiando input..."
rclone copy "${service}:${remote_in}/" "${local_in}/"

echo "Executando..."
srun --mpi=pmix_v2 singularity run \
     --bind=/scratch:/scratch \
     --bind=/var/spool/slurm:/var/spool/slurm \
     Singularity.simg


echo "Enviando output..."
rclone move "${local_out}" "${service}:${remote_out}/"
rclone move "${SLURM_JOB_ID}.out" "${service}:${remote_out}/"

