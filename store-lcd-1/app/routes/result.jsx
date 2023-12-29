import { json } from "@remix-run/node"; // or cloudflare/deno
import { useLoaderData } from "@remix-run/react";
import db from "../db.server";
import { unauthenticated} from "../shopify.server";


import { LoaderFunctionArgs } from "@remix-run/node";

//import '@shopify/shopify-api/adapters/node';
//import {shopifyApi, LATEST_API_VERSION} from '@shopify/shopify-api';

export async function loader({ request }) {
	
  const shopData = await db.Session.findFirst();
	
  const mySession = await unauthenticated.admin(shopData.shop);
  
    const today = new Date();
    //today.setDate(today.getDate()+1);
	let year = today.getUTCFullYear();
	let month = today.getUTCMonth();
	let day = today.getDate();    
    let todaydate = year+'-'+month+'-'+day;
    
	const d = new Date();
	d.setDate(d.getDate() - 7);
	//2019-12-01
	year = d.getUTCFullYear();
	month = d.getUTCMonth();
	day = d.getDate();
	let date = year+'-'+month+'-'+day;
 
const response = await mySession.admin.graphql( // AND created_at:<`+todaydate+`
  `#graphql
  query {
  orders(first: 100, 
  query: "created_at:>`+date+`") {
    edges {
      node {
        id
        totalPrice
      }
    }
  }
}`
);


const orderData = await response.json();

//console.log(orderData.data.orders.edges[1].node.totalPrice);

let grossSales = 0;

for (let order in orderData.data.orders.edges) 
{ 
	grossSales += Number(orderData.data.orders.edges[order].node.totalPrice);
	//grossSales += order.node.totalPrice; 
}


  return json({ grossSales: grossSales.toFixed(2) }); 
  
  /*
  return json([
    { id: "1", name: "Pants" },
    { id: "2", name: "Jacket" },
  ]);
 */
};
