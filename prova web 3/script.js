// Código JavaScript para interatividade no Front-end [4]
const form = document.getElementById("userDataForm"); // Acessa o formulário pelo ID [18, 19]

form.addEventListener("submit", function (event) {
  // Adiciona um "ouvinte" para o evento 'submit' do formulário [18, 20]
  const nomeInput = document.getElementById("nome"); // Acessa o campo de nome [18, 19]
  const idadeInput = document.getElementById("idade"); // Acessa o campo de idade [18, 19]

  // Validação básica usando JavaScript [21]
  if (nomeInput.value.trim() === "") {
    // Verifica se o campo nome está vazio ou contém apenas espaços [22]
    alert("Por favor, digite seu nome."); // Exibe uma caixa de alerta [23]
    event.preventDefault(); // Impede o envio do formulário se a validação falhar
  }

  const idade = parseInt(idadeInput.value); // Converte o valor da idade para um número inteiro
  if (isNaN(idade) || idade < 1) {
    // Verifica se não é um número ou é menor que 1 [22]
    alert("Por favor, digite uma idade válida (um número maior que zero).");
    [23];
    event.preventDefault(); // Impede o envio do formulário
  }

  // Manipulação simples do DOM: Exemplo de alteração de conteúdo (não impede o submit neste caso, apenas demonstra) [18, 21, 24]
  // Isso é apenas para demonstração; em uma validação real, você impediria o envio antes disso.
  // document.querySelector('h1').textContent = 'Validando e Enviando...'; // Altera o texto do h1 [18, 24]
});

// Exemplo de uso de window.prompt (apenas para demonstração, não integrado ao fluxo principal) [18]
// setTimeout(() => { // Espera 2 segundos antes de executar
//    const userGreeting = prompt('Digite uma saudação para o cabeçalho:'); // Exibe uma caixa de prompt [18]
//    if (userGreeting) {
//        document.querySelector('h1').textContent = userGreeting; // Atualiza o h1 com a saudação [18, 24]
//    }
// }, 2000);
