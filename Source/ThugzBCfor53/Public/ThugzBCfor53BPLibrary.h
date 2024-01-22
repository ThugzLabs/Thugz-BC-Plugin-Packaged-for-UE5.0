// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "JsonObjectConverter.h"
#include "ThugzBCfor53BPLibrary.generated.h"

class FJsonObject;

/**
 *
 */
USTRUCT(BlueprintType)
struct FCreator
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thugz Labs JSON")
    FString Address;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thugz Labs JSON")
    bool Verified;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thugz Labs JSON")
    int32 Share;
};

USTRUCT(BlueprintType)
struct FMetadataJson
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thugz Labs JSON")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thugz Labs JSON")
    FString Symbol;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thugz Labs JSON")
    FString Uri;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thugz Labs JSON")
    int32 SellerFeeBasisPoints;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thugz Labs JSON")
    TArray<FCreator> Creators;
};

USTRUCT(BlueprintType)
struct FNFTData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thugz Labs JSON")
    FString NftMint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thugz Labs JSON")
    FString OwnerAccount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thugz Labs JSON")
    FString MetadataAddress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thugz Labs JSON")
    FMetadataJson MetadataJson;

    // Ajouter les autres champs selon le JSON
};

USTRUCT(BlueprintType)
struct FRootJson
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thugz Labs JSON")
    TArray<FNFTData> Data;
};



UCLASS()
class UThugzBCBPLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Web3 Thugz Labs Plugin")
    static void MakeHelloMoonAPIRequest(const FString& Account, const FString& Barear);

    UFUNCTION(BlueprintCallable, Category = "Web3 Thugz Labs Plugin")
    static FString GetLastJsonResponse();

    UFUNCTION(BlueprintCallable, Category = "Web3 Thugz Labs Plugin")
    static FRootJson ConvertJSONtoStruct(FString JsonString);

private:
    static FString LastJsonResponse;

    static void HandleHelloMoonAPIResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

};


/*
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu.
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/

//GENERATED_UCLASS_BODY()

