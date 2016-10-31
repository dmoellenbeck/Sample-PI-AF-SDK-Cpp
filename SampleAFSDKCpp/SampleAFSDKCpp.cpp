#using <mscorlib.dll> // to use Console::WriteLine
#using <OSIsoft.AFSDK.dll>
#include <stdio.h>
// to printf()
using namespace System;
using namespace OSIsoft::AF;
using namespace OSIsoft::AF::Asset;
using namespace OSIsoft::AF::Time;
// Mark unmanaged code
#pragma unmanaged
void print(char *msg)
{
	printf("%s\n", msg);
}

// Switch back to managed code
#pragma managed

int main()
{
	// Write to the console through managed call
	Console::WriteLine("Hello world from managed method");
	PISystems ^piSystems = gcnew PISystems();
	//AF::PISystem  ^piSystem = piSystems->DefaultPISystem;
	PISystem  ^piSystem = piSystems["MARC-PI2016"];
	AFDatabase ^myDb = piSystem->Databases["AFSDKTest"];
	AFElement ^rootElement = myDb->Elements["Tables"];
	AFElement ^subRootElement = rootElement->Elements["InterpolatedTest"];
	AFAttribute ^myAttribute;
	for each (AFAttribute ^attribute  in subRootElement->Attributes)
	{
		if (attribute->Name == "Attribute2")
		{
			myAttribute = attribute;
			break;
		}
	}
	AFTime startTime = AFTime("*-1d");
	AFTime endTime = AFTime("*");
	AFTimeRange time = AFTimeRange(startTime, endTime);
	//time->StartTime = startTime;
	UnitsOfMeasure::UOM ^uom;
	AFValues^ values = myAttribute->Data->RecordedValues(time, OSIsoft::AF::Data::AFBoundaryType::Inside, uom, System::String::Empty, false, 0);

	for each (AFValue^ value in values)
	{
		AFTime^ time = value->Timestamp;
		Console::WriteLine("Value: " + value->Value->ToString() + ", Timestamp: " + time->LocalTime);
	}

	// use stdio to write to console
	print("hello world from unmanaged method");
	return 0;
}