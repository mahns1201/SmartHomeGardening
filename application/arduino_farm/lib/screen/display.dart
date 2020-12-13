import 'package:firebase_database/ui/firebase_animated_list.dart';
// import 'package:firebase_database/ui/firebase_sorted_list.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_database/firebase_database.dart';



class Display extends StatefulWidget {
  Display({this.app});
  final FirebaseApp app;

  @override
  _DisplayState createState() => _DisplayState();
}

class _DisplayState extends State<Display> {

  final refrenceDatabase = FirebaseDatabase.instance;
  // final movieName = 'MovieTitle';
  // final movieController = TextEditingController();

  DatabaseReference _moviesRef;

  @override
  void initState() {
    final FirebaseDatabase database = FirebaseDatabase(app: widget.app);
    _moviesRef = database.reference().child('arduino');

    super.initState();
  }

  @override
  Widget build(BuildContext context) {

    final ref = refrenceDatabase.reference();

    return Scaffold(
      appBar: AppBar(
        title: Text('실시간 화분 상태'),
      ),
      body: SingleChildScrollView(
        child: Column(
          children: [
            Center(
              child: Container(
                color: Colors.green,
                width: MediaQuery.of(context).size.width,
                height: MediaQuery.of(context).size.height,
                child:
                    Flexible(
                        child: new FirebaseAnimatedList(
                          shrinkWrap: true,
                            query: _moviesRef, itemBuilder: (
                            BuildContext context,
                            DataSnapshot snapshot,

                            Animation<double> animation,
                          int index){
                          return new ListTile(
                            // trailing: IconButton(icon: Icon(Icons.delete), onPressed: () =>
                            //  _moviesRef.child(snapshot.key).remove(),),
                            // subtitle: new Text('test'),
                            title: new Text(
                              snapshot.value['sensor'],
                              textAlign: TextAlign.center,
                              style: TextStyle(fontSize: 25, fontWeight: FontWeight.bold),
                            ),
                          );
                        }
                      ),
                    ),


              ),
            ),
          ],
        ),
      ),
    );
  }
}

/*
import 'package:firebase_database/ui/firebase_animated_list.dart';
// import 'package:firebase_database/ui/firebase_sorted_list.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:firebase_database/firebase_database.dart';



class Display extends StatefulWidget {
  Display({this.app});
  final FirebaseApp app;

  @override
  _DisplayState createState() => _DisplayState();
}

class _DisplayState extends State<Display> {

  final refrenceDatabase = FirebaseDatabase.instance;
  // final movieName = 'MovieTitle';
  // final movieController = TextEditingController();

  DatabaseReference _moviesRef;

  @override
  void initState() {
    final FirebaseDatabase database = FirebaseDatabase(app: widget.app);
    _moviesRef = database.reference().child('arduino');

    super.initState();
  }

  @override
  Widget build(BuildContext context) {

    final ref = refrenceDatabase.reference();

    return Scaffold(
      appBar: AppBar(
        title: Text('Current State'),
      ),
      body: SingleChildScrollView(
        child: Column(
          children: [
            Center(
              child: Container(
                color: Colors.green,
                width: MediaQuery.of(context).size.width,
                height: MediaQuery.of(context).size.height,
                child: Column(
                  children: [
                    Text(
                      movieName,
                      textAlign: TextAlign.center,
                      style: TextStyle(fontSize: 25, fontWeight: FontWeight.bold),
                    ),
                    TextField(
                      controller: movieController,
                      textAlign: TextAlign.center,
                    ),
                    FlatButton(
                      color: Colors.grey,
                      onPressed: () {
                        ref
                            .child('Movies')
                            .push()
                            .child(movieName)
                            .set(movieController.text)
                            .asStream();
                        movieController.clear();
                      },
                      child: Text('Save movie'),
                      textColor: Colors.white,
                    ),
                    Flexible(
                      child: new FirebaseAnimatedList(
                          shrinkWrap: true,
                          query: _moviesRef, itemBuilder: (
                          BuildContext context,
                          DataSnapshot snapshot,

                          Animation<double> animation,
                          int index){
                        return new ListTile(
                          // trailing: IconButton(icon: Icon(Icons.delete), onPressed: () =>
                          //  _moviesRef.child(snapshot.key).remove(),),
                          // subtitle: new Text('test'),
                          title: new Text(
                            snapshot.value['sensor'],
                            textAlign: TextAlign.center,
                            style: TextStyle(fontSize: 25, fontWeight: FontWeight.bold),
                          ),
                        );
                      }
                      ),
                    ),
                  ],
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
*/