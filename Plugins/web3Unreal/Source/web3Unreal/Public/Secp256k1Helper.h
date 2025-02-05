#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "secp256k1_recovery.h"
#include "Account.h"
#include "Secp256k1Helper.generated.h"


/**
 * Exposes functionality that utilizes the bitcoin core secp256k1 library to Blueprints/C++ code
 */
UCLASS()
class WEB3UNREAL_API USecp256k1Helper : public UBlueprintFunctionLibrary{
 GENERATED_BODY()
public:
  UFUNCTION(BlueprintCallable, Category = "Web3.Unreal|Secp256k1")
	  static FString RecoverAddressFromSignature(TArray<uint8> message, FString signature);

 UFUNCTION(BlueprintCallable, Category = "Web3.Unreal|Secp256k1")
   static FAccount GenerateNewAccount();
 
 static FString CalcPublicAddressFromPrivateKey(unsigned char seckey[32]);
 static FString RecoverPublicAddressFromSignature(
  unsigned char msg_hash[32],
  FString signatureHexString);
 static FString CalcFStringPublicAddress(secp256k1_context* ctx, secp256k1_pubkey pubkey);

private:
 static bool GenerateRandomPrivateKey(secp256k1_context* ctx, unsigned char seckey[32]);
};