# doe-egot-dcm
Energy Grid of Things: Distributed Control Module

### Raspi Build Instructions
Additional steps are needed to compile this repository on a Raspi.

For XercesC: 
```bash
sudo apt-get update -y && sudo apt-get install -y libxerces-c-dev
```

## Outgoing_linklayer_notifications thoughts
1.)
deps are messed up tbh. the ecs_dcm_impl.cpp doesnt directly ref it's own .h file, and I replicated that in the ecs_CEA2045DeviceUCM because I couldn't remember why I had set it up that way. honestly i think it might be worth fully reworking the #includes. 

2.) 
not all the incoming message notification happens in the link layer processing. For ex, in EPRI_UCM::ProcessDeviceInfoResponse, the method just passes back the device info to the calling command class, which then updates the DTM. It's necessary to pass back information like this, but I think it would be beneficial to make sure all linklayer notifications happen at the same level, rather then sharing the responsibility between the command classes and the receiver.  
