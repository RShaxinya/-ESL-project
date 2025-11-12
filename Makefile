all:
	echo "Build successful - RGB simulation ready"
	echo "For hardware deployment: connect nRF SDK"
	
clean:
	del rgb_app.exe 2>nul || true
