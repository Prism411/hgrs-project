import 'dart:async';

import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

void main() {
  runApp(MyApp());
}

class MyApp extends StatefulWidget {
  @override
  _MyAppState createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  String currentLetter = '';
  List<String> sentence = [];
  Timer? _timer; // Adiciona um campo para armazenar a referência ao Timer

  @override
  void initState() {
    super.initState();
    _startFetchingLetters();
  }

  void _startFetchingLetters() {
    // Inicia o Timer para chamar fetchLetter a cada 500ms
    _timer = Timer.periodic(Duration(milliseconds: 2000), (timer) {
      fetchLetter();
    });
  }

  @override
  void dispose() {
    _timer?.cancel(); // Cancela o Timer ao descartar o widget
    super.dispose();
  }

  void fetchLetter() async {
  try {
    final url = Uri.parse('http://localhost:8080'); // Ajuste conforme necessário
    final response = await http.get(url);
    if (response.statusCode == 200) {
      setState(() {
        currentLetter = response.body.trim();
        sentence.add(currentLetter); // Adiciona automaticamente a letra à frase
      });
    } else {
      print('Falha ao carregar letra: ${response.statusCode}');
    }
  } catch (e) {
    print('Erro ao fazer requisição: $e');
  }
}

  void addSpace() {
    setState(() {
      sentence.add(' ');
    });
  }

  void addLetterToSentence() {
    setState(() {
      sentence.add(currentLetter);
      fetchLetter(); // Buscar a próxima letra após adicionar a atual à frase
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: Text('Tradutor de Libras'),
          centerTitle: true, // Centraliza o título
        ),
        body: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            // Exibe a letra recebida em grande e centralizada
            Text(
              currentLetter,
              style: TextStyle(fontSize: 100, fontWeight: FontWeight.bold),
              textAlign: TextAlign.center,
            ),
            // Espaçamento vertical
            SizedBox(height: 20),
            // Container para a linha de frases
            Expanded(
              child: ListView(
                children: sentence
                    .map((letter) => Center(
                          child: Text(
                            letter,
                            style: TextStyle(fontSize: 24),
                          ),
                        ))
                    .toList(),
              ),
            ),
            // Botão de espaço
            Padding(
              padding: const EdgeInsets.all(8.0),
              child: ElevatedButton(
                onPressed: addSpace,
                child: Text('Espaço'),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
