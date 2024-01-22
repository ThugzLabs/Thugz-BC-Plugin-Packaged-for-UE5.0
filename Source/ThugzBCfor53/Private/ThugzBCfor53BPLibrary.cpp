// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThugzBCfor53BPLibrary.h"
#include "ThugzBCfor53.h"




FString UThugzBCBPLibrary::LastJsonResponse = FString("");

void UThugzBCBPLibrary::MakeHelloMoonAPIRequest(const FString& Account, const FString& Barear)
{
    FString HelloMoonURL = TEXT("https://rest-api.hellomoon.io/v0/nft/mints-by-owner"); // Remplacez par l'URL de votre endpoint HelloMoon

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

    HttpRequest->SetVerb(TEXT("POST"));
    HttpRequest->SetURL(HelloMoonURL);
    HttpRequest->SetHeader(TEXT("Accept"), TEXT("application/json"));
    HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    HttpRequest->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *Barear));
    //HttpRequest->SetHeader(TEXT("Authorization"), TEXT("Bearer 84fc727a-66fd-4f4c-a723-17adb50ce7ca"));

    FString JsonPayload = FString::Printf(TEXT("{\"ownerAccount\":\"%s\"}"), *Account);
    HttpRequest->SetContentAsString(JsonPayload);

    HttpRequest->OnProcessRequestComplete().BindStatic(&UThugzBCBPLibrary::HandleHelloMoonAPIResponse);

    HttpRequest->ProcessRequest();
}

void UThugzBCBPLibrary::HandleHelloMoonAPIResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!bWasSuccessful)
    {
        // Gérer l'erreur de la requête ici
        LastJsonResponse = FString(""); // Réinitialisez la réponse JSON en cas d'erreur
        return;
    }

    if (Response.IsValid() && Response->GetResponseCode() == 200)
    {
        FString JsonResponse = Response->GetContentAsString();
        LastJsonResponse = JsonResponse; // Stockez la réponse JSON

        // Vous pouvez maintenant utiliser JsonResponse qui contient la réponse JSON

        // Par exemple, vous pouvez désérialiser la chaîne JSON en une structure Unreal Engine
    }
    else
    {
        // Gérer l'erreur de réponse HTTP ici
        LastJsonResponse = FString("ERREUR"); // Réinitialisez la réponse JSON en cas d'erreur
    }

}

FString UThugzBCBPLibrary::GetLastJsonResponse()
{
    return LastJsonResponse;
}

FRootJson UThugzBCBPLibrary::ConvertJSONtoStruct(FString JsonString)
{

    FString YourJsonFString; // Votre JSON ici
    TSharedPtr<FJsonObject> JsonObject;
    FRootJson RootStruct;

    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
    if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
    {

        TArray<TSharedPtr<FJsonValue>> DataArray = JsonObject->GetArrayField("data");

        for (int32 i = 0; i < DataArray.Num(); i++)
        {
            TSharedPtr<FJsonObject> DataObject = DataArray[i]->AsObject();

            FNFTData NFTData;
            NFTData.NftMint = DataObject->GetStringField("nftMint");
            NFTData.OwnerAccount = DataObject->GetStringField("ownerAccount");
            NFTData.MetadataAddress = DataObject->GetStringField("metadataAddress");

            // Désérialiser MetadataJson
            TSharedPtr<FJsonObject> MetadataJsonObject = DataObject->GetObjectField("metadataJson");
            NFTData.MetadataJson.Name = MetadataJsonObject->GetStringField("name");
            NFTData.MetadataJson.Symbol = MetadataJsonObject->GetStringField("symbol");
            NFTData.MetadataJson.Uri = MetadataJsonObject->GetStringField("uri");
            NFTData.MetadataJson.SellerFeeBasisPoints = MetadataJsonObject->GetNumberField("sellerFeeBasisPoints");
            // Répéter pour d'autres champs
            // Désérialiser le tableau des créateurs
            TArray<TSharedPtr<FJsonValue>> CreatorsArray = MetadataJsonObject->GetArrayField("creators");
            for (int32 j = 0; j < CreatorsArray.Num(); j++)
            {
                TSharedPtr<FJsonObject> CreatorObject = CreatorsArray[j]->AsObject();

                FCreator Creator;
                Creator.Address = CreatorObject->GetStringField("address");
                Creator.Verified = CreatorObject->GetBoolField("verified");
                Creator.Share = CreatorObject->GetIntegerField("share");

                NFTData.MetadataJson.Creators.Add(Creator);
            }

            // Ajouter l'objet NFTData à la structure racine
            RootStruct.Data.Add(NFTData);
        }
    }
    return RootStruct;
}

