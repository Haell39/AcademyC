<?php
// process.php (Back-end)

// Define uma constante [7]
define("SAUDACAO", "Olá");

// Função simples para demonstrar funções [29]
function exibirMensagem($nome, $idade) {
    global $SAUDACAO; // Acessa a constante global, embora define() torne a constante disponível globalmente [9]
    $mensagem = SAUDACAO . ", " . $nome . "! Você tem " . $idade . " anos."; // Concatenação de strings usando '.' [30]
    return $mensagem; // Retorna um valor [31]
}

// Verifica se a requisição foi feita usando o método POST
// $_SERVER é uma variável Super Global que contém informações sobre o servidor e o ambiente de execução [7, 9]
if ($_SERVER["REQUEST_METHOD"] == "POST") { // Estrutura condicional 'if' [10]

    // Variáveis Super Globais $_POST são usadas para coletar dados de formulários enviados via método POST [7, 27]
    // Filtra e armazena os dados em variáveis PHP [8]
    $nome = htmlspecialchars($_POST['nome']); // htmlspecialchars() é uma função embutida para segurança [32]
    $idade = (int)$_POST['idade']; // Converte a idade para inteiro [8]

    // --- Exemplos de outros conceitos PHP (não diretamente ligados ao formulário) ---

    // Exemplo de Array Indexado [33, 34]
    $frutasFavoritas = ["Maçã", "Banana", "Morango"];
    // echo "Minhas frutas favoritas: " . implode(", ", $frutasFavoritas) . "<br>"; // implode é função embutida de array
    // echo "Total de frutas: " . count($frutasFavoritas) . "<br>"; // Função count() [35, 36]

    // Exemplo de Array Associativo [33, 34]
    $dadosUsuario = [
        "nome" => $nome,
        "idade" => $idade,
        "cidade" => "Exemplo" // Adicionando outro dado
    ];
    // echo "Dados do usuário: Nome: " . $dadosUsuario['nome'] . ", Idade: " . $dadosUsuario['idade'] . "<br>";

    // Exemplo de Loop For [35, 37]
    // echo "Contando até sua idade: ";
    // for ($i = 1; $i <= $idade; $i++) {
    //    echo $i . ($i == $idade ? "" : ", ");
    // }
    // echo "<br>";

    // Exemplo de Loop While [35, 38]
    // $contador = 0;
    // echo "Contando de novo: ";
    // while($contador < 3) {
    //     echo $contador + 1 . " ";
    //     $contador++; // Operador de incremento [30]
    // }
    // echo "<br>";


    // --- Processamento dos dados recebidos ---

    echo "<h1>Processamento PHP</h1>"; // Output para o navegador [32]
    echo "<p>";

    // Chama a função para obter a mensagem [31]
    $mensagemFinal = exibirMensagem($nome, $idade);
    echo $mensagemFinal;

    echo "</p>";

    // Exemplo de Estrutura Condicional else if e else [10]
    if ($idade < 18) {
        echo "<p>Você é menor de idade.</p>";
    } elseif ($idade >= 18 && $idade < 60) { // Uso do operador lógico 'E' (&&) [39] e operadores de comparação [40]
        echo "<p>Você é um adulto.</p>";
    } else {
        echo "<p>Você é um idoso.</p>";
    }

    // Exemplo de Estrutura Condicional Switch [10, 41]
    // switch (true) { // Usando 'true' para avaliar intervalos
    //     case ($idade < 12):
    //         echo "<p>Você é uma criança.</p>";
    //         break;
    //     case ($idade >= 12 && $idade < 18):
    //         echo "<p>Você é um adolescente.</p>";
    //         break;
    //     // Mais casos...
    //     default:
    //         // Mensagem padrão se nenhum caso corresponder
    //         break;
    // }


} else {
    // Se a requisição não for POST (ex: acesso direto ao process.php pela URL)
    echo "<h1>Acesso Inválido</h1>";
    echo "<p>Este arquivo deve ser acessado via formulário POST.</p>";
}

?>