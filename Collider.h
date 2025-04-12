#pragma once
struct Collider
{
	//Everyone gets a collider

	Collider();
	~Collider();

	void OnCollisionEnter(Collider _other);
	void OnCollisionStay(Collider _other);
	void OnCollisionExit(Collider _other);







};

