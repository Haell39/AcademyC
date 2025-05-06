<?php
session_start(); // Inicia a sessão

if (!isset($_SESSION["nomes"])) {
    $_SESSION["nomes"] = array();
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $nome = $_POST["nome"];
    if (empty($nome)) {
        echo "<p class = 'erro>Nome é obrigatório.</p>";
    } else {
        array_push($_SESSION["nomes", $nome]);
        echo "<p class='sucesso'>Registrado com sucesso!</p>";
    }
}

echo "<h2>Lista de Nomes</h2><ul>";
foreach ($_SESSION["nomes"] as $n) {
    echo "<li>" . htmlspecialchars($n) . "</li>";
}
echo "</ul>";
?>