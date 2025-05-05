<?php
session_start();

// Inicializa o array de alunos se não existir
if (!isset($_SESSION["alunos"])) {
    $_SESSION["alunos"] = array();
}

// Função para calcular a média das notas
function calcularMedia($alunos) {
    if (count($alunos) === 0) {
        return 0;
    }
    $soma = 0;
    foreach ($alunos as $aluno) {
        $soma += $aluno["nota"];
    }
    return $soma / count($alunos);
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $nome = trim($_POST["nome"]);
    $nota = floatval($_POST["nota"]);

    // Validação no servidor
    if (empty($nome)) {
        echo "<p class='erro'>Erro: Nome é obrigatório!</p>";
    } elseif ($nota < 0 || $nota > 10) {
        echo "<p class='erro'>Erro: Nota deve estar entre 0 e 10!</p>";
    } else {
        // Adiciona o aluno ao array
        array_push($_SESSION["alunos"], array("nome" => $nome, "nota" => $nota));
        echo "<p class='sucesso'>Aluno registrado com sucesso!</p>";
    }
}

// Exibe a lista de alunos
echo "<h2>Lista de Alunos</h2>";
if (count($_SESSION["alunos"]) === 0) {
    echo "<p>Nenhum aluno registrado.</p>";
} else {
    echo "<ul>";
    foreach ($_SESSION["alunos"] as $aluno) {
        echo "<li>" . htmlspecialchars($aluno["nome"]) . " - Nota: " . number_format($aluno["nota"], 1) . "</li>";
    }
    echo "</ul>";
    echo "<p>Média das notas: " . number_format(calcularMedia($_SESSION["alunos"]), 2) . "</p>";
}

echo "<a href='index.html'>Voltar ao formulário</a>";
?>