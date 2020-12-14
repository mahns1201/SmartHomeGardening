import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:firebase_database/firebase_database.dart';


class Control extends StatefulWidget {
  static const String id = 'switch_screen';

  @override
  _ControlState createState() => _ControlState();
}

class _ControlState extends State<Control> {
  final DBref = FirebaseDatabase.instance.reference();

  bool isSwitched;
  bool newVal;


  void led_on() async {
    await DBref
        .update({'LED_STATUS': 'ON'});
  }

  void led_off() async {
    await DBref
        .update({'LED_STATUS': 'OFF'});
  }

  void watering_on() async {
    await DBref
        .update({'WATERING_STATUS': 'ON'});
  }

  void watering_off() async {
    await DBref
        .update({'WATERING_STATUS': 'OFF'});
  }

  void drain_water_on() async {
    await DBref
        .update({'BOTTLE_STATUS': 'ON'});
  }

  void drain_water_off() async {
    await DBref
        .update({'BOTTLE_STATUS': 'OFF'});
  }



  /*
  void getStatus() async {
    String newValue = (await FirebaseDatabase.instance
        .reference()
        .child("LED_STATUS/DATA")
        .once())
        .value;
    print(isSwitched);
    print(newValue);
    setState(() {
      if (newValue == 'TRUE') {
        isSwitched = true;
      }
      else {
        isSwitched = false;
      }
    });
  }


  @override
  void initState() {
    getStatus();
    super.initState();
  }
  */

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Scaffold(
          appBar: AppBar(
            title: Text('원격 제어'),
          ),

          backgroundColor: Colors.white,
          body: Column(
            children: <Widget>[
              FlatButton(
                shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(20)),
                color: Colors.blue,
                onPressed: () {
                  led_on();
                  print('ON');
                },
                child: Text(
                  'LED ON',
                  textAlign: TextAlign.center,
                  style: TextStyle(fontSize: 25, fontWeight: FontWeight.bold),
                ),
              ),

              FlatButton(
                shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(20)),
                color: Colors.red,
                onPressed: () {
                  led_off();
                  print('OFF');
                },
                child: Text(
                  'LED OFF',
                  textAlign: TextAlign.center,
                  style: TextStyle(fontSize: 25, fontWeight: FontWeight.bold),
                ),
              ),

              FlatButton(
                shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(20)),
                color: Colors.blue,
                onPressed: () {
                  watering_on();
                  print('ON');
                },
                child: Text(
                  '물주기',
                  textAlign: TextAlign.center,
                  style: TextStyle(fontSize: 25, fontWeight: FontWeight.bold),
                ),
              ),

              FlatButton(
                shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(20)),
                color: Colors.red,
                onPressed: () {
                  watering_off();
                  print('OFF');
                },
                child: Text(
                  '물주기 멈춤',
                  textAlign: TextAlign.center,
                  style: TextStyle(fontSize: 25, fontWeight: FontWeight.bold),
                ),
              ),

              FlatButton(
                shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(20)),
                color: Colors.blue,
                onPressed: () {
                  drain_water_on();
                  print('ON');
                },
                child: Text(
                  '물통 비우기',
                  textAlign: TextAlign.center,
                  style: TextStyle(fontSize: 25, fontWeight: FontWeight.bold),
                ),
              ),

              FlatButton(
                shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(20)),
                color: Colors.red,
                onPressed: () {
                  drain_water_off();
                  print('OFF');
                },
                child: Text(
                  '물통 비우기 멈춤',
                  textAlign: TextAlign.center,
                  style: TextStyle(fontSize: 25, fontWeight: FontWeight.bold),
                ),
              ),
            ],
          )),
    );
  }
}
