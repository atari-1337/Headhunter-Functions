// add these to where the functions get registered
rbx_pushcclosure(rl, custom_funcs::readfile);
rbx_setglobal(rl, "readfile");

rbx_pushcclosure(rl, custom_funcs::writefile);
rbx_setglobal(rl, "writefile");

rbx_pushcclosure(rl, custom_funcs::setclipboard);
rbx_setglobal(rl, "setclipboard");
