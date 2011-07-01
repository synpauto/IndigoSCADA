/*
 *                         IndigoSCADA
 *
 *   This software and documentation are Copyright 2002 to 2009 Enscada 
 *   Limited and its licensees. All rights reserved. See file:
 *
 *                     $HOME/LICENSE 
 *
 *   for full copyright notice and license terms. 
 *
 */


/*
*Iec104driver driver 
*
*/

#include <qt.h>
#include "iec104driver.h"
#include "iec104driver_instance.h"
#include "general_defines.h"

/*
*Function:Iec104driver
*Inputs:none
*Outputs:none
*Returns:none
*/
Iec104driver::Iec104driver(QObject *parent,const QString &name) : Driver(parent,name),n_opc_items(0)
{
	connect (GetConfigureDb (),
	SIGNAL (TransactionDone (QObject *, const QString &, int, QObject*)), this,
	SLOT (QueryResponse (QObject *, const QString &, int, QObject*)));	// connect to the database
};
/*
*Function:~Iec104driver
*Inputs:none
*Outputs:none
*Returns:none
*/
Iec104driver::~Iec104driver()
{
};
/*
*Function:UnitConfigure
*Inputs:parent widget, unit name
*Outputs:none
*Returns:none
*/
void Iec104driver::UnitConfigure(QWidget *parent, const QString &name, const QString &receipe) // configure a unit
{
	Iec104driverConfiguration dlg(parent,name,receipe);
	dlg.exec();   
};
/*
*Function:UnitConfigure
*Inputs:parent widget, unit name
*Outputs:none
*Returns:none
*/
void Iec104driver::CommandDlg(QWidget *parent, const QString &name) // command dialog
{
	Iec104driverCommand dlg(parent,name);
	dlg.exec();   
};
/*
*Function:SetTypeList
*Inputs:combo , unit name
*Outputs:none
*Returns:none
*/
void Iec104driver::SetTypeList(QComboBox *pCombo, const QString &unitname) // set the type list for unit type
{
	pCombo->insertItem(TYPE_M_SP_NA_1);
	pCombo->insertItem(TYPE_M_ME_TC_1);
	pCombo->insertItem(TYPE_M_SP_TA_1);
	pCombo->insertItem(TYPE_M_ME_NB_1);
	pCombo->insertItem(TYPE_M_ME_TB_1);
};
/*
*Function:GetInputList
*Inputs:type
*Outputs:list of input indices
*Returns:none
*/
void Iec104driver::GetInputList(const QString &type, QStringList &list,const QString &, const QString &) // set the permitted input IDs
{
/*
	if(type == TYPE_M_ME_TC_1)
	{
		list << "01" << "02" << "03" << "04" << "05" << "06" << "07" << "08" 
		<< "09" << "10" << "11" << "12" << "13" << "14" << "15" << "16";         
	}

	if(type == TYPE_M_SP_NA_1)
	{
		list << "01" << "02" << "03" << "04" << "05" << "06" << "07" << "08" 
		<< "09" << "10" << "11" << "12" << "13" << "14" << "15" << "16";         
	}
*/
};
/*
*Function:GetSpecificConfig
*Inputs:parent , sample point name, sample point type
*Outputs:none
*Returns:none
*/
QWidget * Iec104driver::GetSpecificConfig(QWidget *parent, const QString &spname, const QString &sptype) //specific config for sample point of type
{
	Iec104driverInput * p;
	if(sptype == TYPE_M_ME_TC_1)
	{
		p = new Iec104driverInput(parent,spname);
		return p;
	}
	else if (sptype == TYPE_M_SP_NA_1)
	{
		p = new Iec104driverInput(parent,spname);
		return p;
	}
	else if (sptype == TYPE_M_SP_TA_1)
	{
		p = new Iec104driverInput(parent,spname);
		return p;
	}

	return 0;
};
/*
*Function:GetTagList
*Inputs:type
*Outputs:permitted tag list for unit
*Returns:none
*/
void Iec104driver::GetTagList(const QString &type, QStringList &list,const QString &,const QString &) // returns the permitted tags for a given type for this unit
{
	if(type == TYPE_M_ME_TC_1)
	{
		list << VALUE_TAG;
	}
	else if (type == TYPE_M_SP_NA_1)
	{
		list << BIT_TAG;
	}
	else if (type == TYPE_M_SP_TA_1)
	{
		list << BIT_TAG;
	}
};
/*
*Function:Command
*pass a command to a unit
*Inputs:unit name, command
*Outputs:none
*Returns:none
*/
void Iec104driver::Command(const QString & instance,BYTE cmd, LPVOID lpPa, DWORD pa_length, DWORD ipindex)
{
	IT_IT("Iec104driver::Command");

	IDict::iterator i = Instances.find(instance);

	if(!(i == Instances.end()))
	{
		(*i).second->Command(instance, cmd, lpPa, pa_length, ipindex); // pass on the command to the instance of the driver
	};
};
/*
*Function:CreateNewUnit
*Inputs:parent widget , unit name
*Outputs:none
*Returns:none
*/
void Iec104driver::CreateNewUnit(QWidget *parent, const QString &name, int n_inputs) // create a new unit - quick configure
{
	n_opc_items = n_inputs;
	iec_unit_name = name;
	
	QString n;
	n.sprintf("%02d",1);
	QString spname = name+"Point"+n;
	
	QString pc = 
	"select * from PROPS where SKEY='SAMPLEPROPS' and IKEY='" + spname +"';"; 
	//
	// get the properties SKEY = unit name IKEY = receipe name
	GetConfigureDb()->DoExec(this,pc, tcreateNewUnit);
};
//
Iec104driver * Iec104driver::pDriver = 0; // only one instance should be created
/*
*Function: Start
*Inputs:none
*Outputs:none
*Returns:none
*/
void Iec104driver::Start() // start everything under this driver's control
{
		QString cmd = "select * from UNITS where UNITTYPE='iec104driver' and NAME in(" + DriverInstance::FormUnitList()+ ");";
		GetConfigureDb()->DoExec(this,cmd,tListUnits);
};
/*
*Function: Stop
*Inputs:none
*Outputs:none
*Returns:none
*/
void Iec104driver::Stop() // stop everything under this driver's control
{
	// ask each instance to stop 
	IDict::iterator i = Instances.begin();

	for(; !(i == Instances.end());i++)
	{
		(*i).second->Stop();
	};
	//
	// now delete them
	//     
	i = Instances.begin();

	for(; !(i == Instances.end());i++)
	{
		delete (*i).second;
	};
	//  
	Instances.clear();
};
/*
*Function:QueryResponse
*Inputs:client object, command, transaction id
*Outputs:none
*Returns:none
*/
void Iec104driver::QueryResponse (QObject *p, const QString &, int id, QObject*caller)
{
	if(this != p) return;
	switch(id)
	{  
		case tListUnits:
		{
			int n = GetConfigureDb()->GetNumberResults();
			if(n > 0)
			{
				for(int i = 0; i < n; i++,GetConfigureDb()->FetchNext())
				{
					QString unit_name = GetConfigureDb()->GetString("NAME");
					Iec104driver_Instance *p = new Iec104driver_Instance(this, unit_name);
					IDict::value_type pr(unit_name, p);
					Instances.insert(pr);
					p->Start(); // kick it off 
				};
			};
		};
		break;
		case tcreateNewUnit:
		{
			if(GetConfigureDb()->GetNumberResults() == 0)
			{
				for(int i = 1 ; i <= n_opc_items; i++)
				{
					QString n;
					n.sprintf("%02d",i);
					QString spname = iec_unit_name+"Point"+n;
					//
					QString cmd = 
					QString("insert into SAMPLE values('") + spname + 
					QString("',' Point Number ")  + n + "','" + iec_unit_name + 
					QString("','"TYPE_M_SP_TA_1"','sp',1,1,'") + n + "',0,0,0);";
					// 
					GetConfigureDb()->DoExec(0,cmd,0); // post it off

					QStringList l;
					GetTagList(TYPE_M_SP_TA_1,l,"","");

					QString m;
					m.sprintf("%d",i);

					CreateSamplePoint(spname, l, m);
				};
			}
		}
		break;
		default:
		break;
	};   
};

// ********************************************************************************************************************************
/*
*Function:GetDriverEntry
*Inputs:parent object
*Outputs:none
*Returns:driver interface 
*/
extern "C"
{ 
	#ifdef WIN32
	IEC_104_DRIVERDRV Driver *  _cdecl _GetDriverEntry(QObject *parent); 
	IEC_104_DRIVERDRV void _cdecl _Unload();
	#endif
	Driver *  _cdecl  _GetDriverEntry(QObject *parent) 
	{
		if(!Iec104driver::pDriver)
		{
			Iec104driver::pDriver = new Iec104driver(parent,"Iec104driver");
		};
		return Iec104driver::pDriver;
	};
	/*
	*Function: _Unload
	*clean up before DLL unload. and QObjects must be deleted or we get a prang
	*Inputs:none
	*Outputs:none
	*Returns:none
	*/
	void _cdecl _Unload()
	{
		if(Iec104driver::pDriver) delete Iec104driver::pDriver;
		Iec104driver::pDriver = 0;
	};
};

