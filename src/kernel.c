void main()
{
	const char* message = "Hello, World!(C)";
	volatile char* video_memory = (volatile char*)0xB8000;
	for(int i = 0; message[i] != '\0'; i++)
	{
		video_memory[i*2] = message[i];
		video_memory[i*2+1] = 0x02;
	}
	while(1);
}
