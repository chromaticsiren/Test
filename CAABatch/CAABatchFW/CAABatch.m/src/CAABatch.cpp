// COPYRIGHT Dassault Systemes 2015
//
// Usage:
//      mkrun -c "TSTBatch <Repository> <Server Name> <Server Port> <Server RootURI> <Login Ticket>"
//
//===================================================================

#include "CATUnicodeString.h"
#include "CATPLMSessionServices.h"
#include "CATAdpPublicSecurityServices.h"

#include <iostream>

//-------------------------------------------------------------------------
// InitPLMSession
//-------------------------------------------------------------------------
HRESULT Init3DEXPERIENCESession (CATUnicodeString & iRepository, CATUnicodeString & iServerName, CATUnicodeString & iServerPort, CATUnicodeString & iServerRootURI, CATUnicodeString & iLoginTicket)
{
   HRESULT rc = E_INVALIDARG;
   if (iRepository != "" && iServerName != "" && iServerPort != "" && iServerRootURI != "" && iLoginTicket != "")
   {
      rc = CATPLMSessionServices::SetPLMSessionParameter ("Repository",    iRepository);				  
      if (SUCCEEDED(rc))  rc = CATPLMSessionServices::SetPLMSessionParameter ("ServerName",      iServerName);
      if (SUCCEEDED(rc))  rc = CATPLMSessionServices::SetPLMSessionParameter ("ServerPort",      iServerPort);
      if (SUCCEEDED(rc))  rc = CATPLMSessionServices::SetPLMSessionParameter ("ServerRootURI",   iServerRootURI);
      if (SUCCEEDED(rc))  rc = CATPLMSessionServices::SetPLMSessionParameter ("LoginTicket",     iLoginTicket);
      if (SUCCEEDED(rc))  rc = CATPLMSessionServices::SetPLMSessionParameter ("ServerProtocol",  "http");

      if (SUCCEEDED(rc))  rc = CATPLMSessionServices::InitPLMSession();
   }
   return rc;
}

//-------------------------------------------------------------------------
// main
//-------------------------------------------------------------------------
int main(int iargc, char *iargv[])
{
     using std::cout;
     using std::endl;


   // Initialization
   HRESULT rc = S_OK;

   // Check if all the arguments have been valuated 
   int nb_RequestedArguments = 5;
   if ((iargc - 1) < nb_RequestedArguments)
   {

      cout << "\nIt miss " << nb_RequestedArguments - (iargc-1) << " arguments. We need " << nb_RequestedArguments << " arguments:"	<< endl
           << "\t 1- Repository"		                  << endl
           << "\t 2- Server Name"		               << endl
           << "\t 3- Server Port"		               << endl
           << "\t 4- Server RootURI"   	            << endl
           << "\t 5- Login Ticket"                    << endl << endl;
      rc = E_FAIL;   
   }
   else if ((iargc - 1) > nb_RequestedArguments)
   {
      cout << "Too many arguments "	<< "(" << iargc - 1 << ") We need " << nb_RequestedArguments << " arguments" << endl << endl;
      rc = E_FAIL;   
   }
   if (FAILED(rc))
   {
      int nb_Arguments = iargc-1;
      cout << endl << "Number of arguments : " << nb_Arguments << endl;
      for (int i = 1; i <= nb_Arguments; i++)
      {
         cout << "   Argument[" << i << "] = " << iargv[i] << endl;
      }
   }

   // 3DEXPERIENCE session initialization
   if (SUCCEEDED(rc))
   {
      CATUnicodeString Repository     = iargv[1];
      CATUnicodeString ServerName     = iargv[2];
      CATUnicodeString ServerPort     = iargv[3];
      CATUnicodeString ServerRootURI  = iargv[4];
      CATUnicodeString LoginTicket    = iargv[5];

      cout << "\nInitializing session with:"	                      << endl
           << "\tRepository         = ["  << Repository     << "]" << endl
           << "\tServer Name        = ["  << ServerName	   << "]" << endl
           << "\tServer Port        = ["  << ServerPort	   << "]" << endl
           << "\tServer RootURI     = ["  << ServerRootURI  << "]" << endl
           << "\tLogin Ticket       = ["  << LoginTicket    << "]" << endl << endl;
      rc = Init3DEXPERIENCESession (Repository, ServerName, ServerPort, ServerRootURI, LoginTicket);

      if (SUCCEEDED(rc))
      {
         CATString ConnectedUser, OrganisationId, ProjectId, RoleId;
         rc = CATAdpPublicSecurityServices::GetSecurityParameters (Repository, ConnectedUser, OrganisationId, ProjectId, RoleId);
         if (SUCCEEDED(rc))
         {
            cout << endl << "   Connection succeeded" << endl;
            cout << "         " << ConnectedUser << "   (" << RoleId << "   " << OrganisationId << "  " << ProjectId << ") is connected" << endl << endl;
         }
      }
      else
         cout << endl << "   Connection failed" << endl << endl;
   }




   // Your process
   // ...
   // ...




   // Close the 3DEXPERIENCE session initialization
   CATPLMSessionServices::ClosePLMSession();

   if (SUCCEEDED(rc))  return 0;
   cout << endl << "  --> Batch failed!" << endl << endl;
                       return 1;
}
