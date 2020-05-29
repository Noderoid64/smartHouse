import 'package:android_client/widgets/add-new-device-icon/new-device-dialog/new-device-dialog.viewmodel.dart';
import 'package:flutter/material.dart';
import 'package:provider_architecture/provider_architecture.dart';

import '../../ssid-dropdown.widget.dart';

class NewDeviceDialogWidget extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return ViewModelProvider<NewDeviceDialogViewModel>.withConsumer(
        viewModel: NewDeviceDialogViewModel(),
        builder: (context, model, child) =>
            SimpleDialog(title: Text("Add device to network"), children: [
              Container(
                  padding: EdgeInsets.all(18.0),
                  child: Form(
                    key: model.formKey,
                    child: Column(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: <Widget>[
                          SsidDropdownWidget(null, model.getSsid),
                          TextFormField(
                            decoration: const InputDecoration(
                              hintText: 'Password',
                            ),
                            validator: model.ssidValidatorFunction,
                            controller: model.ssidController,
                          ),
                          Padding(
                              padding: EdgeInsets.fromLTRB(0.0, 10.0, 0.0, 0.0),
                              child: RaisedButton(
                                onPressed: model.submitButtonPressed,
                                color: Colors.lightGreen[700],
                                child: Text('Submit'),
                              ))
                        ]),
                  ))
            ]));
  }
}
