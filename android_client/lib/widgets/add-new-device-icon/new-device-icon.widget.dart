import 'package:android_client/widgets/add-new-device-icon/new-device-icon.viewmodel.dart';
import 'package:flutter/material.dart';

import 'package:provider_architecture/provider_architecture.dart';

class NewDeviceIconWidget extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return ViewModelProvider<NewDeviceIconViewModel>.withConsumer(
        viewModel: NewDeviceIconViewModel(),
        builder: (context, model, child) => IconButton(
              icon: Icon(Icons.add_circle),
              iconSize: 40.0,
              color: Colors.lightGreen[500],
              onPressed: model.showDialog,
            ));
  }
}

//    return IconButton(
//      icon: Icon(Icons.add_circle),
//      iconSize: 40.0,
//      color: Colors.lightGreen[500],
//      onPressed: () async {
//        await showDialog(
//            context: context,
//            builder: (BuildContext context) {
//              return SimpleDialog(
//                title: Text("Add device to network"),
//                children: [
//                  Container(
//                    padding: EdgeInsets.all(18.0),
//                    child: Form(
//                      key: _formKey,
//                      child: Column(
//                        crossAxisAlignment:
//                        CrossAxisAlignment.start,
//                        children: <Widget>[
//                          SsidDropdownWidget(_ssidTextKey),
//                          TextFormField(
//                            key: _passwordTextKey,
//                            decoration: const InputDecoration(
//                              hintText: 'Password',
//                            ),
//                            validator: (value) {
//                              if (value.isEmpty) {
//                                return 'Please enter some text';
//                              } else if (value.length < 8) {
//                                return 'Please enter more than 8 chars';
//                              }
//                              return null;
//                            },
//                          ),
//                          Padding(
//                              padding: EdgeInsets.fromLTRB(
//                                  0.0, 10.0, 0.0, 0.0),
//                              child: RaisedButton(
//                                onPressed: () {
//                                  if (_formKey.currentState.validate()) {
//                                    String ssid = _ssidTextKey.currentState.value;
//                                    String pass = _passwordTextKey.currentState.value;
//                                    log(ssid);
//                                    log(pass);
//                                    socketRestService.login(ssid, pass).then((bool response) {
//                                      if (response) {
//                                        log("Ok");
//                                      } else {
//                                        log("Sorry");
//                                      }
//                                    });
//                                  }
//                                },
//                                color: Colors.lightGreen[700],
//                                child: Text('Submit'),
//                              ))
//                        ],
//                      ),
//                    ),
//                  )
//                ],
//              );
//            });
//      },
//    );
//  }
//}
