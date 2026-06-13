from fastapi import APIRouter, Depends, HTTPException, Request
from fastapi.templating import Jinja2Templates
from sqlalchemy import text
from sqlalchemy.orm import Session
from api.app.database import get_db

router = APIRouter(
    prefix="/heroes"
)

templates = Jinja2Templates(directory="templates")

@router.get("/")
def get_all_heroes(request: Request, db: Session = Depends(get_db)):
    heroes = db.execute(
        text("SELECT * FROM heroes;")
    ).mappings().all()

    return templates.TemplateResponse(
        request=request,
        name="heroes.html",
        context={"heroes": heroes}
    )

@router.get("/{id}")
def get_one_hero(id: int, db: Session = Depends(get_db)):
    result = db.execute(
        text("SELECT * FROM heroes WHERE id = :id;"),
        {"id": id}
    ).mappings().first()

    if not result:
        raise HTTPException(status_code=404, detail="Hero not found")

    return {
        "hero": dict(result)
    }

@router.delete("/{id}")
def delete_one_hero(id: int, db: Session = Depends(get_db)):
    result = db.execute(
        text("DELETE FROM heroes WHERE id = :id;"),
        {"id": id}
    ).mappings().first()

    if not result:
        raise HTTPException(status_code=404, detail="Hero not found")

    return {
        "hero": dict(result)
    }

@router.put("/{id}/{studs}")
def add_virtual_studs(id: int, studs: int, db: Session = Depends(get_db)):
    result = db.execute(
        text("UPDATE heroes SET virtual_studs_count = virtual_studs_count + :studs WHERE id = :id"),
        {"id": id, "studs": studs}
    )

    if result.rowcount == 0:
        raise HTTPException(status_code=404, detail="Hero not found")

    db.commit()

    updated_hero = db.execute(
        text("SELECT * FROM heroes WHERE id = :id"),
        {"id": id}
    ).first()

    if updated_hero:
        return {
            "hero": dict(updated_hero._mapping)
        }


