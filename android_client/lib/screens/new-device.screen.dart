import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class NewDeviceScreen extends StatelessWidget {

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Connect device'),
      ),
      body: Center(
        child: MyCustomForm(),
      ),
    );
  }
}


class MyCustomForm extends StatefulWidget {
  @override
  MyCustomFormState createState() {
    return MyCustomFormState();
  }
}

// Create a corresponding State class.
// This class holds data related to the form.
class MyCustomFormState extends State<MyCustomForm> {
  final _formKey = GlobalKey<FormState>();

  String ssid;
  String pass;

  @override
  Widget build(BuildContext context) {
    // Build a Form widget using the _formKey created above.
    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 16.0, vertical: 16.0),
      child: Form(
        key: _formKey,
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.center,
          children: <Widget>[
            TextFormField(
              decoration: InputDecoration(
                  labelText: 'Enter network ssid'
              ),
              validator: (value) {
                if (value.isEmpty) {
                  return 'Please enter some text';
                }
                return null;
              },
              onChanged: (text) {
                ssid = text;
              },
            ),
            TextFormField(
              decoration: InputDecoration(
                  labelText: 'Password'
              ),
              validator: (value) {
                if (value.isEmpty) {
                  return 'Please enter some text';
                }
                return null;
              },
              onChanged: (text) {
                pass = text;
              },
            ),
            Padding(
              padding: const EdgeInsets.symmetric(vertical: 16.0),
              child: RaisedButton(
                color: Colors.lightGreen[700],
                onPressed: () {
//                  // Validate returns true if the form is valid, or false
//                  // otherwise.
//                  if (_formKey.currentState.validate()) {
//                    deviceRestService.login(ssid, pass).then((bool result) => {
//
//                        Scaffold.of(context)
//                        .showSnackBar(
//                        SnackBar(content: Text(result ? "Device connected to $ssid" : "Not connected")))
//
//                });
//
//                }
                },
                child: Text('Submit'),
              ),
            ),
          ],
        ),
      ),
    );
  }
}