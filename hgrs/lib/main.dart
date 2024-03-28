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
  Timer? _timer; // Campo para armazenar a referência ao Timer

  @override
  void initState() {
    super.initState();
    _startFetchingLetters();
  }

  void _startFetchingLetters() {  
    _timer = Timer.periodic(Duration(milliseconds: 200), (timer) {
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
    final url = Uri.parse('http://192.168.100.3:8080');
    final response = await http.get(url);
    if (response.statusCode == 200) {
      final letter = response.body.trim();
      // Verifica se a letra é válida e diferente da atual antes de atualizar
      // Além disso, evita tratar entradas vazias ou espaços como letras válidas
      if (letter.isNotEmpty && isLetter(letter) && letter != currentLetter) {
        setState(() {
          currentLetter = letter;
          sentence.add(currentLetter); // Adiciona a letra válida à frase
        });
      }
    } else {
      print('Falha ao carregar letra: ${response.statusCode}');
    }
  } catch (e) {
    print('Erro ao fazer requisição: $e');
  }
} 

bool isLetter(String str) {
  return str.isNotEmpty && str.runes.every((r) {
    var char = String.fromCharCode(r);
    return char.contains(RegExp(r'^[a-zA-Z]$'));
  });
}

  void addSpace() {
    setState(() {
      sentence.add(' ');
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: Text('Tradutor de Libras'),
          centerTitle: true,
        ),
        body: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Text(
              currentLetter,
              style: TextStyle(fontSize: 100, fontWeight: FontWeight.bold),
              textAlign: TextAlign.center,
            ),
            SizedBox(height: 20),
            // Altera o container para horizontal
            Container(
              height: 60, // Define uma altura para o container
              child: ListView(
                scrollDirection: Axis.horizontal, // Define a direção do scroll para horizontal
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
