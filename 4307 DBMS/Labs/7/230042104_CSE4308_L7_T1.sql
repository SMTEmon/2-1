create table customer(
    userID varchar(10) primary key,
    email varchar(100),
    namee varchar(100),
    default_shipping_address varchar(100)
);

create table order(
    orderID varchar(10) primary key,
    order_date date,
    stat varchar(10)
);

create table categories(
    namee varchar(20) primary key,
    categoryID int,
);

create table products(
    SKU varchar(10) primary key,
    namee varchar(100),
    descript varchar(200),
    stockQuantity int,
    price int,
    categoryID int,

    foreign key (categoryID) references categories(categoryID),

    constrain check validStock stockQuantity >= 0,
    constrain check validPrice price >= 0;
);

create table shipping(
    TrackingNum int primary key,
    carrier varchar(30),
    EstimatedDelivery date
);

create table payment(
    PaymentID varchar(10),
    amount int,
    methodd varchar(10),
    paymentDate date
);

create table orderRecord(
    orderID varchar(10),
    userID varchar(10),
    PaymentID varchar(10),
    TrackingNum int,
    SKU varchar(10),
    quantityOrdered int,

    primary key(orderID, userID),

    foreign key (orderID) references order(orderID) on delete cascade,
    foreign key (SKU) references products(SKU) on delete cascade,
    foreign key (PaymentID) references payment(PaymentID),
    foreign key (TrackingNum) references shipping(TrackingNum),
    foreign key (userID) references customer(userID)
);