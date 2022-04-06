// #include "Keypad.h"

// void Keypad_Init(Control *mem)
// {

//     // CREATE_PASS(control_ptr);
//     //  Create_Pass();
//     //  check for stored password, if none:
//     //  Note >> This needs to be relayed to other peers (eventually)
//     mem->system_state = 0;
// }

// void Keypad_Loop(Control *mem)
// {

//     // if (mem->system_state == 0)
//     // {
//     //     mem->system_state = 1;
//     // }

//     // Await for somem kind of state change to enable the system
//     // if (mem->system_state == 1)
//     // {
//     //     //Check for a gpio high
//     //     ENABLE_SYS(mem);
//     // }

//     // Await for somem kind of state change to disable the system
//     // if (mem->system_state == 2)
//     // {
//     //     //Check for disable or alarm call
//     //      Check pin from HP_Loop
//     //     AWAIT_ALARM();
//     //      Check pin for keyboard (touch)
//     //     DISABLE_SYS(mem);
//     // }

//     // If in await alarm state, give 10 seconds to disarm
//     if (mem->system_state == 4)
//     {
//         delay(10000);
//         if (CHECK_PASS() > 0)
//         {
//             DISABLE_SYS(mem);
//         }
//         else
//         {
//             RAISE_ALARM(mem);
//         }
//     }

//     // If in alarm state, give option to reset
//     if (mem->system_state == 5)
//     {
//         if (CHECK_PASS() > 0)
//         {
//             DISABLE_SYS(mem);
//         }
//         else
//         {
//             // RING SOME SHIT
//         }
//     }
// }
