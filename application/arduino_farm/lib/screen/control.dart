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
        // .child("LED_STATUS")
        .update({'LED_STATUS': 'ON'});
  }

  void led_off() async {
    await DBref
        .update({'LED_STATUS': 'OFF'});
        // .child("LED_STATUS")
        // .update({'DATA': 'FALSE'});
  }

  void watering_on() async {
    await DBref
        .child("WATERING_STATUS")
        .update({'DATA': 'TRUE'});
  }

  void watering_off() async {
    await DBref
        .child("WATERING_STATUS")
        .update({'DATA': 'FALSE'});
  }

  void fan_on() async {
    await DBref
        .child("FAN_STATUS")
        .update({'DATA': 'TRUE'});
  }

  void fan_off() async {
    await DBref
        .child("FAN_STATUS")
        .update({'DATA': 'FALSE'});
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
                  'Watering ON',
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
                  'Watering OFF',
                  textAlign: TextAlign.center,
                  style: TextStyle(fontSize: 25, fontWeight: FontWeight.bold),
                ),
              ),

              FlatButton(
                shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(20)),
                color: Colors.blue,
                onPressed: () {
                  fan_on();
                  print('ON');
                },
                child: Text(
                  'FAN ON',
                  textAlign: TextAlign.center,
                  style: TextStyle(fontSize: 25, fontWeight: FontWeight.bold),
                ),
              ),

              FlatButton(
                shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(20)),
                color: Colors.red,
                onPressed: () {
                  fan_off();
                  print('OFF');
                },
                child: Text(
                  'FAN OFF',
                  textAlign: TextAlign.center,
                  style: TextStyle(fontSize: 25, fontWeight: FontWeight.bold),
                ),
              ),
            ],
          )),
    );
  }
}
