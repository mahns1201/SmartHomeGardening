import 'package:flutter/material.dart';

import 'package:arduino_farm/screen/display.dart';
import 'package:arduino_farm/screen/control.dart';
import 'package:arduino_farm/screen/test.dart';    // temporary
import 'package:arduino_farm/widget/bottom.dart';


class MainScreen extends StatefulWidget {
  @override
  _MainScreenState createState() => _MainScreenState();
}

class _MainScreenState extends State<MainScreen> {

  TabController _controller;

  void initState(){
    super.initState();
    print('MainScreen initsate');
  }

  void dispose() {
    _controller.dispose();
    print('MainScreen dispose');
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      // title: 'PlanBreaker',
      theme: ThemeData(
          brightness: Brightness.light,
          primaryColor: Colors.green,
          accentColor: Colors.white),
      home: DefaultTabController(
        length: 3,
        child: Scaffold(
          body: TabBarView(
            physics: NeverScrollableScrollPhysics(),
            children: <Widget>[
              Display(),
              Control(),
              Test(),
            ],
          ),
          bottomNavigationBar: Bottom(),
        ),
      ),
    );
  }
}

