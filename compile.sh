
gcc -Wno-format -o admin-bin admin.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic


<<<<<<< HEAD
<<<<<<< HEAD
gcc -Wno-format -o client-bin client.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0` -export-dynamic



=======
gcc -Wno-format -o client-bin client.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
>>>>>>> eb4f344df4ee88f933b9138174b647f68458a93e
=======
gcc -Wno-format -o client-bin client.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
>>>>>>> eb4f344df4ee88f933b9138174b647f68458a93e
